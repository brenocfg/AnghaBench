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
struct hfi1_pportdata {scalar_t__ link_enabled; scalar_t__ driver_link_ready; } ;
struct hfi1_devdata {int /*<<< orphan*/  flags; struct hfi1_pportdata* pport; } ;

/* Variables and functions */
 int FREEZE_ABORT ; 
 int FREEZE_SELF ; 
 int /*<<< orphan*/  HFI1_FORCED_FREEZE ; 
 int OPA_LINKDOWN_REASON_SMA_DISABLED ; 
 int PLS_OFFLINE ; 
 int /*<<< orphan*/  dc_shutdown (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  dd_dev_emerg (struct hfi1_devdata*,char*) ; 
 int /*<<< orphan*/  set_physical_link_state (struct hfi1_devdata*,int) ; 
 int /*<<< orphan*/  start_freeze_handling (struct hfi1_pportdata*,int) ; 

__attribute__((used)) static void handle_temp_err(struct hfi1_devdata *dd)
{
	struct hfi1_pportdata *ppd = &dd->pport[0];
	/*
	 * Thermal Critical Interrupt
	 * Put the device into forced freeze mode, take link down to
	 * offline, and put DC into reset.
	 */
	dd_dev_emerg(dd,
		     "Critical temperature reached! Forcing device into freeze mode!\n");
	dd->flags |= HFI1_FORCED_FREEZE;
	start_freeze_handling(ppd, FREEZE_SELF | FREEZE_ABORT);
	/*
	 * Shut DC down as much and as quickly as possible.
	 *
	 * Step 1: Take the link down to OFFLINE. This will cause the
	 *         8051 to put the Serdes in reset. However, we don't want to
	 *         go through the entire link state machine since we want to
	 *         shutdown ASAP. Furthermore, this is not a graceful shutdown
	 *         but rather an attempt to save the chip.
	 *         Code below is almost the same as quiet_serdes() but avoids
	 *         all the extra work and the sleeps.
	 */
	ppd->driver_link_ready = 0;
	ppd->link_enabled = 0;
	set_physical_link_state(dd, (OPA_LINKDOWN_REASON_SMA_DISABLED << 8) |
				PLS_OFFLINE);
	/*
	 * Step 2: Shutdown LCB and 8051
	 *         After shutdown, do not restore DC_CFG_RESET value.
	 */
	dc_shutdown(dd);
}