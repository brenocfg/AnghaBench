#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct MPT3SAS_ADAPTER {int dummy; } ;
struct TYPE_3__ {int ReasonCode; int /*<<< orphan*/  ASCQ; int /*<<< orphan*/  ASC; int /*<<< orphan*/  TaskTag; int /*<<< orphan*/  WWID; int /*<<< orphan*/  DevHandle; } ;
typedef  TYPE_1__ Mpi26EventDataPCIeDeviceStatusChange_t ;

/* Variables and functions */
#define  MPI26_EVENT_PCIDEV_STAT_RC_ABORT_TASK_SET_INTERNAL 139 
#define  MPI26_EVENT_PCIDEV_STAT_RC_ASYNC_NOTIFICATION 138 
#define  MPI26_EVENT_PCIDEV_STAT_RC_CLEAR_TASK_SET_INTERNAL 137 
#define  MPI26_EVENT_PCIDEV_STAT_RC_CMP_INTERNAL_DEV_RESET 136 
#define  MPI26_EVENT_PCIDEV_STAT_RC_CMP_TASK_ABORT_INTERNAL 135 
#define  MPI26_EVENT_PCIDEV_STAT_RC_DEV_INIT_FAILURE 134 
#define  MPI26_EVENT_PCIDEV_STAT_RC_INTERNAL_DEVICE_RESET 133 
#define  MPI26_EVENT_PCIDEV_STAT_RC_PCIE_HOT_RESET_FAILED 132 
#define  MPI26_EVENT_PCIDEV_STAT_RC_QUERY_TASK_INTERNAL 131 
#define  MPI26_EVENT_PCIDEV_STAT_RC_SMART_DATA 130 
#define  MPI26_EVENT_PCIDEV_STAT_RC_TASK_ABORT_INTERNAL 129 
#define  MPI26_EVENT_PCIDEV_STAT_RC_UNSUPPORTED 128 
 int /*<<< orphan*/  ioc_info (struct MPT3SAS_ADAPTER*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 

__attribute__((used)) static void
_scsih_pcie_device_status_change_event_debug(struct MPT3SAS_ADAPTER *ioc,
	Mpi26EventDataPCIeDeviceStatusChange_t *event_data)
{
	char *reason_str = NULL;

	switch (event_data->ReasonCode) {
	case MPI26_EVENT_PCIDEV_STAT_RC_SMART_DATA:
		reason_str = "smart data";
		break;
	case MPI26_EVENT_PCIDEV_STAT_RC_UNSUPPORTED:
		reason_str = "unsupported device discovered";
		break;
	case MPI26_EVENT_PCIDEV_STAT_RC_INTERNAL_DEVICE_RESET:
		reason_str = "internal device reset";
		break;
	case MPI26_EVENT_PCIDEV_STAT_RC_TASK_ABORT_INTERNAL:
		reason_str = "internal task abort";
		break;
	case MPI26_EVENT_PCIDEV_STAT_RC_ABORT_TASK_SET_INTERNAL:
		reason_str = "internal task abort set";
		break;
	case MPI26_EVENT_PCIDEV_STAT_RC_CLEAR_TASK_SET_INTERNAL:
		reason_str = "internal clear task set";
		break;
	case MPI26_EVENT_PCIDEV_STAT_RC_QUERY_TASK_INTERNAL:
		reason_str = "internal query task";
		break;
	case MPI26_EVENT_PCIDEV_STAT_RC_DEV_INIT_FAILURE:
		reason_str = "device init failure";
		break;
	case MPI26_EVENT_PCIDEV_STAT_RC_CMP_INTERNAL_DEV_RESET:
		reason_str = "internal device reset complete";
		break;
	case MPI26_EVENT_PCIDEV_STAT_RC_CMP_TASK_ABORT_INTERNAL:
		reason_str = "internal task abort complete";
		break;
	case MPI26_EVENT_PCIDEV_STAT_RC_ASYNC_NOTIFICATION:
		reason_str = "internal async notification";
		break;
	case MPI26_EVENT_PCIDEV_STAT_RC_PCIE_HOT_RESET_FAILED:
		reason_str = "pcie hot reset failed";
		break;
	default:
		reason_str = "unknown reason";
		break;
	}

	ioc_info(ioc, "PCIE device status change: (%s)\n"
		 "\thandle(0x%04x), WWID(0x%016llx), tag(%d)",
		 reason_str, le16_to_cpu(event_data->DevHandle),
		 (u64)le64_to_cpu(event_data->WWID),
		 le16_to_cpu(event_data->TaskTag));
	if (event_data->ReasonCode == MPI26_EVENT_PCIDEV_STAT_RC_SMART_DATA)
		pr_cont(", ASC(0x%x), ASCQ(0x%x)\n",
			event_data->ASC, event_data->ASCQ);
	pr_cont("\n");
}