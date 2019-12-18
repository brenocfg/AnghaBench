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
struct myrb_hba {scalar_t__ new_ev_seq; int need_err_info; int need_ldev_info; int need_rbld; int rbld_first; int need_cc_status; int /*<<< orphan*/  host; scalar_t__ secondary_monitor_time; int /*<<< orphan*/  bgi_status_supported; int /*<<< orphan*/  need_bgi_status; int /*<<< orphan*/  old_ev_seq; struct myrb_enquiry* enquiry; int /*<<< orphan*/  enquiry_addr; } ;
struct TYPE_2__ {scalar_t__ deferred; } ;
struct myrb_enquiry {int ldev_count; scalar_t__ ev_seq; scalar_t__ ldev_offline; scalar_t__ pdev_dead; scalar_t__ rbld; int /*<<< orphan*/  ldev_critical; TYPE_1__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_CRIT ; 
 int /*<<< orphan*/  KERN_INFO ; 
#define  MYRB_BG_CHECK_IN_PROGRESS 136 
#define  MYRB_BG_RBLD_IN_PROGRESS 135 
#define  MYRB_BG_RBLD_OR_CHECK_FAILED_DRIVE_FAILED 134 
#define  MYRB_BG_RBLD_OR_CHECK_FAILED_LDEV_FAILED 133 
#define  MYRB_BG_RBLD_OR_CHECK_FAILED_OTHER 132 
#define  MYRB_BG_RBLD_OR_CHECK_SUCCESS_TERMINATED 131 
 int /*<<< orphan*/  MYRB_CMD_ENQUIRY ; 
#define  MYRB_NO_STDBY_RBLD_OR_CHECK_IN_PROGRESS 130 
 scalar_t__ MYRB_SECONDARY_MONITOR_INTERVAL ; 
 unsigned short MYRB_STATUS_SUCCESS ; 
#define  MYRB_STDBY_RBLD_COMPLETED_WITH_ERROR 129 
#define  MYRB_STDBY_RBLD_IN_PROGRESS 128 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  memcpy (struct myrb_enquiry*,struct myrb_enquiry*,int) ; 
 unsigned short myrb_exec_type3 (struct myrb_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ time_after_eq (scalar_t__,scalar_t__) ; 

__attribute__((used)) static unsigned short myrb_hba_enquiry(struct myrb_hba *cb)
{
	struct myrb_enquiry old, *new;
	unsigned short status;

	memcpy(&old, cb->enquiry, sizeof(struct myrb_enquiry));

	status = myrb_exec_type3(cb, MYRB_CMD_ENQUIRY, cb->enquiry_addr);
	if (status != MYRB_STATUS_SUCCESS)
		return status;

	new = cb->enquiry;
	if (new->ldev_count > old.ldev_count) {
		int ldev_num = old.ldev_count - 1;

		while (++ldev_num < new->ldev_count)
			shost_printk(KERN_CRIT, cb->host,
				     "Logical Drive %d Now Exists\n",
				     ldev_num);
	}
	if (new->ldev_count < old.ldev_count) {
		int ldev_num = new->ldev_count - 1;

		while (++ldev_num < old.ldev_count)
			shost_printk(KERN_CRIT, cb->host,
				     "Logical Drive %d No Longer Exists\n",
				     ldev_num);
	}
	if (new->status.deferred != old.status.deferred)
		shost_printk(KERN_CRIT, cb->host,
			     "Deferred Write Error Flag is now %s\n",
			     (new->status.deferred ? "TRUE" : "FALSE"));
	if (new->ev_seq != old.ev_seq) {
		cb->new_ev_seq = new->ev_seq;
		cb->need_err_info = true;
		shost_printk(KERN_INFO, cb->host,
			     "Event log %d/%d (%d/%d) available\n",
			     cb->old_ev_seq, cb->new_ev_seq,
			     old.ev_seq, new->ev_seq);
	}
	if ((new->ldev_critical > 0 &&
	     new->ldev_critical != old.ldev_critical) ||
	    (new->ldev_offline > 0 &&
	     new->ldev_offline != old.ldev_offline) ||
	    (new->ldev_count != old.ldev_count)) {
		shost_printk(KERN_INFO, cb->host,
			     "Logical drive count changed (%d/%d/%d)\n",
			     new->ldev_critical,
			     new->ldev_offline,
			     new->ldev_count);
		cb->need_ldev_info = true;
	}
	if (new->pdev_dead > 0 ||
	    new->pdev_dead != old.pdev_dead ||
	    time_after_eq(jiffies, cb->secondary_monitor_time
			  + MYRB_SECONDARY_MONITOR_INTERVAL)) {
		cb->need_bgi_status = cb->bgi_status_supported;
		cb->secondary_monitor_time = jiffies;
	}
	if (new->rbld == MYRB_STDBY_RBLD_IN_PROGRESS ||
	    new->rbld == MYRB_BG_RBLD_IN_PROGRESS ||
	    old.rbld == MYRB_STDBY_RBLD_IN_PROGRESS ||
	    old.rbld == MYRB_BG_RBLD_IN_PROGRESS) {
		cb->need_rbld = true;
		cb->rbld_first = (new->ldev_critical < old.ldev_critical);
	}
	if (old.rbld == MYRB_BG_CHECK_IN_PROGRESS)
		switch (new->rbld) {
		case MYRB_NO_STDBY_RBLD_OR_CHECK_IN_PROGRESS:
			shost_printk(KERN_INFO, cb->host,
				     "Consistency Check Completed Successfully\n");
			break;
		case MYRB_STDBY_RBLD_IN_PROGRESS:
		case MYRB_BG_RBLD_IN_PROGRESS:
			break;
		case MYRB_BG_CHECK_IN_PROGRESS:
			cb->need_cc_status = true;
			break;
		case MYRB_STDBY_RBLD_COMPLETED_WITH_ERROR:
			shost_printk(KERN_INFO, cb->host,
				     "Consistency Check Completed with Error\n");
			break;
		case MYRB_BG_RBLD_OR_CHECK_FAILED_DRIVE_FAILED:
			shost_printk(KERN_INFO, cb->host,
				     "Consistency Check Failed - Physical Device Failed\n");
			break;
		case MYRB_BG_RBLD_OR_CHECK_FAILED_LDEV_FAILED:
			shost_printk(KERN_INFO, cb->host,
				     "Consistency Check Failed - Logical Drive Failed\n");
			break;
		case MYRB_BG_RBLD_OR_CHECK_FAILED_OTHER:
			shost_printk(KERN_INFO, cb->host,
				     "Consistency Check Failed - Other Causes\n");
			break;
		case MYRB_BG_RBLD_OR_CHECK_SUCCESS_TERMINATED:
			shost_printk(KERN_INFO, cb->host,
				     "Consistency Check Successfully Terminated\n");
			break;
		}
	else if (new->rbld == MYRB_BG_CHECK_IN_PROGRESS)
		cb->need_cc_status = true;

	return MYRB_STATUS_SUCCESS;
}