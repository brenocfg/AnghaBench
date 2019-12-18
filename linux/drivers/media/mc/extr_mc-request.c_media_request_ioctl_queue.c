#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct media_request {scalar_t__ state; int /*<<< orphan*/  debug_str; int /*<<< orphan*/  lock; struct media_device* mdev; } ;
struct media_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  req_queue_mutex; TYPE_1__* ops; } ;
typedef  enum media_request_state { ____Placeholder_media_request_state } media_request_state ;
struct TYPE_2__ {int (* req_validate ) (struct media_request*) ;int /*<<< orphan*/  (* req_queue ) (struct media_request*) ;} ;

/* Variables and functions */
 long EBUSY ; 
 scalar_t__ MEDIA_REQUEST_STATE_IDLE ; 
 scalar_t__ MEDIA_REQUEST_STATE_QUEUED ; 
 int MEDIA_REQUEST_STATE_VALIDATING ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  media_request_get (struct media_request*) ; 
 int /*<<< orphan*/  media_request_put (struct media_request*) ; 
 int media_request_state_str (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct media_request*) ; 
 int /*<<< orphan*/  stub2 (struct media_request*) ; 

__attribute__((used)) static long media_request_ioctl_queue(struct media_request *req)
{
	struct media_device *mdev = req->mdev;
	enum media_request_state state;
	unsigned long flags;
	int ret;

	dev_dbg(mdev->dev, "request: queue %s\n", req->debug_str);

	/*
	 * Ensure the request that is validated will be the one that gets queued
	 * next by serialising the queueing process. This mutex is also used
	 * to serialize with canceling a vb2 queue and with setting values such
	 * as controls in a request.
	 */
	mutex_lock(&mdev->req_queue_mutex);

	media_request_get(req);

	spin_lock_irqsave(&req->lock, flags);
	if (req->state == MEDIA_REQUEST_STATE_IDLE)
		req->state = MEDIA_REQUEST_STATE_VALIDATING;
	state = req->state;
	spin_unlock_irqrestore(&req->lock, flags);
	if (state != MEDIA_REQUEST_STATE_VALIDATING) {
		dev_dbg(mdev->dev,
			"request: unable to queue %s, request in state %s\n",
			req->debug_str, media_request_state_str(state));
		media_request_put(req);
		mutex_unlock(&mdev->req_queue_mutex);
		return -EBUSY;
	}

	ret = mdev->ops->req_validate(req);

	/*
	 * If the req_validate was successful, then we mark the state as QUEUED
	 * and call req_queue. The reason we set the state first is that this
	 * allows req_queue to unbind or complete the queued objects in case
	 * they are immediately 'consumed'. State changes from QUEUED to another
	 * state can only happen if either the driver changes the state or if
	 * the user cancels the vb2 queue. The driver can only change the state
	 * after each object is queued through the req_queue op (and note that
	 * that op cannot fail), so setting the state to QUEUED up front is
	 * safe.
	 *
	 * The other reason for changing the state is if the vb2 queue is
	 * canceled, and that uses the req_queue_mutex which is still locked
	 * while req_queue is called, so that's safe as well.
	 */
	spin_lock_irqsave(&req->lock, flags);
	req->state = ret ? MEDIA_REQUEST_STATE_IDLE
			 : MEDIA_REQUEST_STATE_QUEUED;
	spin_unlock_irqrestore(&req->lock, flags);

	if (!ret)
		mdev->ops->req_queue(req);

	mutex_unlock(&mdev->req_queue_mutex);

	if (ret) {
		dev_dbg(mdev->dev, "request: can't queue %s (%d)\n",
			req->debug_str, ret);
		media_request_put(req);
	}

	return ret;
}