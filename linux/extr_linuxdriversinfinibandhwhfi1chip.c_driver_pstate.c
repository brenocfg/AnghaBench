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
struct hfi1_pportdata {int host_link_state; int /*<<< orphan*/  dd; } ;

/* Variables and functions */
#define  HLS_DN_DISABLE 138 
#define  HLS_DN_DOWNDEF 137 
#define  HLS_DN_OFFLINE 136 
#define  HLS_DN_POLL 135 
#define  HLS_GOING_OFFLINE 134 
#define  HLS_GOING_UP 133 
#define  HLS_LINK_COOLDOWN 132 
#define  HLS_UP_ACTIVE 131 
#define  HLS_UP_ARMED 130 
#define  HLS_UP_INIT 129 
#define  HLS_VERIFY_CAP 128 
 int IB_PORTPHYSSTATE_DISABLED ; 
 int IB_PORTPHYSSTATE_LINKUP ; 
 int IB_PORTPHYSSTATE_POLLING ; 
 int IB_PORTPHYSSTATE_TRAINING ; 
 int OPA_PORTPHYSSTATE_OFFLINE ; 
 int /*<<< orphan*/  dd_dev_err (int /*<<< orphan*/ ,char*,int) ; 

u32 driver_pstate(struct hfi1_pportdata *ppd)
{
	switch (ppd->host_link_state) {
	case HLS_UP_INIT:
	case HLS_UP_ARMED:
	case HLS_UP_ACTIVE:
		return IB_PORTPHYSSTATE_LINKUP;
	case HLS_DN_POLL:
		return IB_PORTPHYSSTATE_POLLING;
	case HLS_DN_DISABLE:
		return IB_PORTPHYSSTATE_DISABLED;
	case HLS_DN_OFFLINE:
		return OPA_PORTPHYSSTATE_OFFLINE;
	case HLS_VERIFY_CAP:
		return IB_PORTPHYSSTATE_TRAINING;
	case HLS_GOING_UP:
		return IB_PORTPHYSSTATE_TRAINING;
	case HLS_GOING_OFFLINE:
		return OPA_PORTPHYSSTATE_OFFLINE;
	case HLS_LINK_COOLDOWN:
		return OPA_PORTPHYSSTATE_OFFLINE;
	case HLS_DN_DOWNDEF:
	default:
		dd_dev_err(ppd->dd, "invalid host_link_state 0x%x\n",
			   ppd->host_link_state);
		return  -1;
	}
}