#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  long u32 ;
struct file {int dummy; } ;
struct TYPE_3__ {unsigned long a_suspend_req_inf; unsigned long a_bus_drop; unsigned long a_bus_req; unsigned long b_bus_req; } ;
struct TYPE_4__ {long host_working; TYPE_1__ fsm; } ;

/* Variables and functions */
#define  GET_OTG_STATUS 132 
#define  SET_A_BUS_DROP 131 
#define  SET_A_BUS_REQ 130 
#define  SET_A_SUSPEND_REQ 129 
#define  SET_B_BUS_REQ 128 
 TYPE_2__* fsl_otg_dev ; 
 int /*<<< orphan*/  otg_statemachine (TYPE_1__*) ; 

__attribute__((used)) static long fsl_otg_ioctl(struct file *file, unsigned int cmd,
			  unsigned long arg)
{
	u32 retval = 0;

	switch (cmd) {
	case GET_OTG_STATUS:
		retval = fsl_otg_dev->host_working;
		break;

	case SET_A_SUSPEND_REQ:
		fsl_otg_dev->fsm.a_suspend_req_inf = arg;
		break;

	case SET_A_BUS_DROP:
		fsl_otg_dev->fsm.a_bus_drop = arg;
		break;

	case SET_A_BUS_REQ:
		fsl_otg_dev->fsm.a_bus_req = arg;
		break;

	case SET_B_BUS_REQ:
		fsl_otg_dev->fsm.b_bus_req = arg;
		break;

	default:
		break;
	}

	otg_statemachine(&fsl_otg_dev->fsm);

	return retval;
}