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
struct hfi1_pportdata {int /*<<< orphan*/  freeze_work; int /*<<< orphan*/  offline_disabled_reason; int /*<<< orphan*/  start_link_work; int /*<<< orphan*/  qsfp_retry_count; scalar_t__ link_enabled; scalar_t__ driver_link_ready; struct hfi1_devdata* dd; } ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI1_ODR_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HLS_DN_OFFLINE ; 
 int /*<<< orphan*/  MAX_QSFP_RETRIES ; 
 int /*<<< orphan*/  OPA_LINKDOWN_REASON_REBOOT ; 
 int /*<<< orphan*/  RCV_CTRL_RCV_PORT_ENABLE_SMASK ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_rcvctrl (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_link_down_reason (struct hfi1_pportdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_link_state (struct hfi1_pportdata*,int /*<<< orphan*/ ) ; 

void hfi1_quiet_serdes(struct hfi1_pportdata *ppd)
{
	struct hfi1_devdata *dd = ppd->dd;

	/*
	 * Shut down the link and keep it down.   First turn off that the
	 * driver wants to allow the link to be up (driver_link_ready).
	 * Then make sure the link is not automatically restarted
	 * (link_enabled).  Cancel any pending restart.  And finally
	 * go offline.
	 */
	ppd->driver_link_ready = 0;
	ppd->link_enabled = 0;

	ppd->qsfp_retry_count = MAX_QSFP_RETRIES; /* prevent more retries */
	flush_delayed_work(&ppd->start_link_work);
	cancel_delayed_work_sync(&ppd->start_link_work);

	ppd->offline_disabled_reason =
			HFI1_ODR_MASK(OPA_LINKDOWN_REASON_REBOOT);
	set_link_down_reason(ppd, OPA_LINKDOWN_REASON_REBOOT, 0,
			     OPA_LINKDOWN_REASON_REBOOT);
	set_link_state(ppd, HLS_DN_OFFLINE);

	/* disable the port */
	clear_rcvctrl(dd, RCV_CTRL_RCV_PORT_ENABLE_SMASK);
	cancel_work_sync(&ppd->freeze_work);
}