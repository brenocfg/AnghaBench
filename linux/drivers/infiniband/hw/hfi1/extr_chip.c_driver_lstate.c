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
 int HLS_DOWN ; 
 int HLS_UP ; 
#define  HLS_UP_ACTIVE 130 
#define  HLS_UP_ARMED 129 
#define  HLS_UP_INIT 128 
 int IB_PORT_ACTIVE ; 
 int IB_PORT_ARMED ; 
 int IB_PORT_DOWN ; 
 int IB_PORT_INIT ; 
 int /*<<< orphan*/  dd_dev_err (int /*<<< orphan*/ ,char*,int) ; 

u32 driver_lstate(struct hfi1_pportdata *ppd)
{
	if (ppd->host_link_state && (ppd->host_link_state & HLS_DOWN))
		return IB_PORT_DOWN;

	switch (ppd->host_link_state & HLS_UP) {
	case HLS_UP_INIT:
		return IB_PORT_INIT;
	case HLS_UP_ARMED:
		return IB_PORT_ARMED;
	case HLS_UP_ACTIVE:
		return IB_PORT_ACTIVE;
	default:
		dd_dev_err(ppd->dd, "invalid host_link_state 0x%x\n",
			   ppd->host_link_state);
	return -1;
	}
}