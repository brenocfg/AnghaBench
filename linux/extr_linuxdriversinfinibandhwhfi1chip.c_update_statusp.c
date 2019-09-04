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
typedef  int u32 ;
struct hfi1_pportdata {int* statusp; int /*<<< orphan*/  dd; } ;

/* Variables and functions */
 int HFI1_STATUS_IB_CONF ; 
 int HFI1_STATUS_IB_READY ; 
#define  IB_PORT_ACTIVE 131 
#define  IB_PORT_ARMED 130 
#define  IB_PORT_DOWN 129 
#define  IB_PORT_INIT 128 
 int /*<<< orphan*/  dd_dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  opa_lstate_name (int) ; 

__attribute__((used)) static void update_statusp(struct hfi1_pportdata *ppd, u32 state)
{
	/*
	 * Set port status flags in the page mapped into userspace
	 * memory. Do it here to ensure a reliable state - this is
	 * the only function called by all state handling code.
	 * Always set the flags due to the fact that the cache value
	 * might have been changed explicitly outside of this
	 * function.
	 */
	if (ppd->statusp) {
		switch (state) {
		case IB_PORT_DOWN:
		case IB_PORT_INIT:
			*ppd->statusp &= ~(HFI1_STATUS_IB_CONF |
					   HFI1_STATUS_IB_READY);
			break;
		case IB_PORT_ARMED:
			*ppd->statusp |= HFI1_STATUS_IB_CONF;
			break;
		case IB_PORT_ACTIVE:
			*ppd->statusp |= HFI1_STATUS_IB_READY;
			break;
		}
	}
	dd_dev_info(ppd->dd, "logical state changed to %s (0x%x)\n",
		    opa_lstate_name(state), state);
}