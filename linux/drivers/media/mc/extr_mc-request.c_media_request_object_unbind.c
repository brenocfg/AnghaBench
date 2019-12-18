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
struct media_request_object {TYPE_1__* ops; int /*<<< orphan*/  completed; struct media_request* req; int /*<<< orphan*/  list; } ;
struct media_request {scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  poll_wait; int /*<<< orphan*/  num_incomplete_objects; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unbind ) (struct media_request_object*) ;} ;

/* Variables and functions */
 scalar_t__ MEDIA_REQUEST_STATE_CLEANING ; 
 scalar_t__ MEDIA_REQUEST_STATE_COMPLETE ; 
 scalar_t__ MEDIA_REQUEST_STATE_QUEUED ; 
 scalar_t__ MEDIA_REQUEST_STATE_VALIDATING ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_request_put (struct media_request*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct media_request_object*) ; 
 int /*<<< orphan*/  wake_up_interruptible_all (int /*<<< orphan*/ *) ; 

void media_request_object_unbind(struct media_request_object *obj)
{
	struct media_request *req = obj->req;
	unsigned long flags;
	bool completed = false;

	if (WARN_ON(!req))
		return;

	spin_lock_irqsave(&req->lock, flags);
	list_del(&obj->list);
	obj->req = NULL;

	if (req->state == MEDIA_REQUEST_STATE_COMPLETE)
		goto unlock;

	if (WARN_ON(req->state == MEDIA_REQUEST_STATE_VALIDATING))
		goto unlock;

	if (req->state == MEDIA_REQUEST_STATE_CLEANING) {
		if (!obj->completed)
			req->num_incomplete_objects--;
		goto unlock;
	}

	if (WARN_ON(!req->num_incomplete_objects))
		goto unlock;

	req->num_incomplete_objects--;
	if (req->state == MEDIA_REQUEST_STATE_QUEUED &&
	    !req->num_incomplete_objects) {
		req->state = MEDIA_REQUEST_STATE_COMPLETE;
		completed = true;
		wake_up_interruptible_all(&req->poll_wait);
	}

unlock:
	spin_unlock_irqrestore(&req->lock, flags);
	if (obj->ops->unbind)
		obj->ops->unbind(obj);
	if (completed)
		media_request_put(req);
}