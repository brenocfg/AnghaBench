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
struct ibmvscsi_host_data {int action; } ;

/* Variables and functions */
#define  IBMVSCSI_HOST_ACTION_NONE 131 
#define  IBMVSCSI_HOST_ACTION_REENABLE 130 
#define  IBMVSCSI_HOST_ACTION_RESET 129 
#define  IBMVSCSI_HOST_ACTION_UNBLOCK 128 
 scalar_t__ kthread_should_stop () ; 

__attribute__((used)) static int __ibmvscsi_work_to_do(struct ibmvscsi_host_data *hostdata)
{
	if (kthread_should_stop())
		return 1;
	switch (hostdata->action) {
	case IBMVSCSI_HOST_ACTION_NONE:
		return 0;
	case IBMVSCSI_HOST_ACTION_RESET:
	case IBMVSCSI_HOST_ACTION_REENABLE:
	case IBMVSCSI_HOST_ACTION_UNBLOCK:
	default:
		break;
	}

	return 1;
}