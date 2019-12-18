#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * prev; } ;
struct sclp_req {int queue_timeout; TYPE_4__ list; int /*<<< orphan*/  sccb; scalar_t__ queue_expires; scalar_t__ start_count; int /*<<< orphan*/  status; } ;
struct TYPE_6__ {int /*<<< orphan*/  expires; } ;

/* Variables and functions */
 int EIO ; 
 int ENODATA ; 
 int HZ ; 
 int /*<<< orphan*/  SCLP_REQ_QUEUED ; 
 int /*<<< orphan*/  __sclp_can_add_request (struct sclp_req*) ; 
 int __sclp_start_request (struct sclp_req*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_add_tail (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (TYPE_4__*) ; 
 int /*<<< orphan*/  mod_timer (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  sclp_lock ; 
 TYPE_1__ sclp_queue_timer ; 
 int /*<<< orphan*/  sclp_req_queue ; 
 scalar_t__ sclp_running_state ; 
 scalar_t__ sclp_running_state_idle ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  timer_pending (TYPE_1__*) ; 

int
sclp_add_request(struct sclp_req *req)
{
	unsigned long flags;
	int rc;

	spin_lock_irqsave(&sclp_lock, flags);
	if (!__sclp_can_add_request(req)) {
		spin_unlock_irqrestore(&sclp_lock, flags);
		return -EIO;
	}
	req->status = SCLP_REQ_QUEUED;
	req->start_count = 0;
	list_add_tail(&req->list, &sclp_req_queue);
	rc = 0;
	if (req->queue_timeout) {
		req->queue_expires = jiffies + req->queue_timeout * HZ;
		if (!timer_pending(&sclp_queue_timer) ||
		    time_after(sclp_queue_timer.expires, req->queue_expires))
			mod_timer(&sclp_queue_timer, req->queue_expires);
	} else
		req->queue_expires = 0;
	/* Start if request is first in list */
	if (sclp_running_state == sclp_running_state_idle &&
	    req->list.prev == &sclp_req_queue) {
		if (!req->sccb) {
			list_del(&req->list);
			rc = -ENODATA;
			goto out;
		}
		rc = __sclp_start_request(req);
		if (rc)
			list_del(&req->list);
	}
out:
	spin_unlock_irqrestore(&sclp_lock, flags);
	return rc;
}