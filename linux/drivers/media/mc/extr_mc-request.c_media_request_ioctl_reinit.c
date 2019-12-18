#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct media_request {scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  debug_str; scalar_t__ access_count; struct media_device* mdev; } ;
struct media_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 long EBUSY ; 
 scalar_t__ MEDIA_REQUEST_STATE_CLEANING ; 
 scalar_t__ MEDIA_REQUEST_STATE_COMPLETE ; 
 scalar_t__ MEDIA_REQUEST_STATE_IDLE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_request_clean (struct media_request*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static long media_request_ioctl_reinit(struct media_request *req)
{
	struct media_device *mdev = req->mdev;
	unsigned long flags;

	spin_lock_irqsave(&req->lock, flags);
	if (req->state != MEDIA_REQUEST_STATE_IDLE &&
	    req->state != MEDIA_REQUEST_STATE_COMPLETE) {
		dev_dbg(mdev->dev,
			"request: %s not in idle or complete state, cannot reinit\n",
			req->debug_str);
		spin_unlock_irqrestore(&req->lock, flags);
		return -EBUSY;
	}
	if (req->access_count) {
		dev_dbg(mdev->dev,
			"request: %s is being accessed, cannot reinit\n",
			req->debug_str);
		spin_unlock_irqrestore(&req->lock, flags);
		return -EBUSY;
	}
	req->state = MEDIA_REQUEST_STATE_CLEANING;
	spin_unlock_irqrestore(&req->lock, flags);

	media_request_clean(req);

	spin_lock_irqsave(&req->lock, flags);
	req->state = MEDIA_REQUEST_STATE_IDLE;
	spin_unlock_irqrestore(&req->lock, flags);

	return 0;
}