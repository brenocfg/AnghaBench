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
 int IB_PORT_ACTIVE ; 
 int IB_PORT_ARMED ; 
 int IB_PORT_DOWN ; 
 int IB_PORT_INIT ; 
#define  LSTATE_ACTIVE 131 
#define  LSTATE_ARMED 130 
#define  LSTATE_DOWN 129 
#define  LSTATE_INIT 128 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*,int) ; 

__attribute__((used)) static u32 chip_to_opa_lstate(struct hfi1_devdata *dd, u32 chip_lstate)
{
	switch (chip_lstate) {
	default:
		dd_dev_err(dd,
			   "Unknown logical state 0x%x, reporting IB_PORT_DOWN\n",
			   chip_lstate);
		/* fall through */
	case LSTATE_DOWN:
		return IB_PORT_DOWN;
	case LSTATE_INIT:
		return IB_PORT_INIT;
	case LSTATE_ARMED:
		return IB_PORT_ARMED;
	case LSTATE_ACTIVE:
		return IB_PORT_ACTIVE;
	}
}