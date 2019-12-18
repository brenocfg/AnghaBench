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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ap_queue {int /*<<< orphan*/  qid; int /*<<< orphan*/  lock; int /*<<< orphan*/  state; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  AP_DBF (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AP_EVENT_POLL ; 
 int /*<<< orphan*/  AP_QID_CARD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AP_QID_QUEUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AP_STATE_RESET_START ; 
 int /*<<< orphan*/  DBF_INFO ; 
 int /*<<< orphan*/  __ap_flush_queue (struct ap_queue*) ; 
 int /*<<< orphan*/  ap_sm_event (struct ap_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ap_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct ap_queue* to_ap_queue (struct device*) ; 

__attribute__((used)) static ssize_t reset_store(struct device *dev,
			   struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct ap_queue *aq = to_ap_queue(dev);

	spin_lock_bh(&aq->lock);
	__ap_flush_queue(aq);
	aq->state = AP_STATE_RESET_START;
	ap_wait(ap_sm_event(aq, AP_EVENT_POLL));
	spin_unlock_bh(&aq->lock);

	AP_DBF(DBF_INFO, "reset queue=%02x.%04x triggered by user\n",
	       AP_QID_CARD(aq->qid), AP_QID_QUEUE(aq->qid));

	return count;
}