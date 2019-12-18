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
struct media_request_object {int completed; struct media_request* req; } ;
struct media_request {scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  poll_wait; int /*<<< orphan*/  num_incomplete_objects; } ;

/* Variables and functions */
 scalar_t__ MEDIA_REQUEST_STATE_COMPLETE ; 
 scalar_t__ MEDIA_REQUEST_STATE_QUEUED ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  media_request_put (struct media_request*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible_all (int /*<<< orphan*/ *) ; 

void media_request_object_complete(struct media_request_object *obj)
{
	struct media_request *req = obj->req;
	unsigned long flags;
	bool completed = false;

	spin_lock_irqsave(&req->lock, flags);
	if (obj->completed)
		goto unlock;
	obj->completed = true;
	if (WARN_ON(!req->num_incomplete_objects) ||
	    WARN_ON(req->state != MEDIA_REQUEST_STATE_QUEUED))
		goto unlock;

	if (!--req->num_incomplete_objects) {
		req->state = MEDIA_REQUEST_STATE_COMPLETE;
		wake_up_interruptible_all(&req->poll_wait);
		completed = true;
	}
unlock:
	spin_unlock_irqrestore(&req->lock, flags);
	if (completed)
		media_request_put(req);
}