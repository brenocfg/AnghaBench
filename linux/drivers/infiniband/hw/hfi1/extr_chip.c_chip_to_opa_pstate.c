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
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int IB_PORTPHYSSTATE_DISABLED ; 
 int IB_PORTPHYSSTATE_LINKUP ; 
 int IB_PORTPHYSSTATE_PHY_TEST ; 
 int IB_PORTPHYSSTATE_POLLING ; 
 int IB_PORTPHYSSTATE_TRAINING ; 
 int OPA_PORTPHYSSTATE_OFFLINE ; 
#define  PLS_CONFIGPHY 133 
#define  PLS_DISABLED 132 
#define  PLS_LINKUP 131 
#define  PLS_OFFLINE 130 
#define  PLS_PHYTEST 129 
#define  PLS_POLLING 128 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*,int) ; 

u32 chip_to_opa_pstate(struct hfi1_devdata *dd, u32 chip_pstate)
{
	/* look at the HFI meta-states only */
	switch (chip_pstate & 0xf0) {
	default:
		dd_dev_err(dd, "Unexpected chip physical state of 0x%x\n",
			   chip_pstate);
		/* fall through */
	case PLS_DISABLED:
		return IB_PORTPHYSSTATE_DISABLED;
	case PLS_OFFLINE:
		return OPA_PORTPHYSSTATE_OFFLINE;
	case PLS_POLLING:
		return IB_PORTPHYSSTATE_POLLING;
	case PLS_CONFIGPHY:
		return IB_PORTPHYSSTATE_TRAINING;
	case PLS_LINKUP:
		return IB_PORTPHYSSTATE_LINKUP;
	case PLS_PHYTEST:
		return IB_PORTPHYSSTATE_PHY_TEST;
	}
}