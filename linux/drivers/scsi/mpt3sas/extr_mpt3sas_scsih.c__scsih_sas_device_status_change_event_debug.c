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
struct TYPE_3__ {int ReasonCode; int /*<<< orphan*/  ASCQ; int /*<<< orphan*/  ASC; int /*<<< orphan*/  TaskTag; int /*<<< orphan*/  SASAddress; int /*<<< orphan*/  DevHandle; } ;
typedef  TYPE_1__ Mpi2EventDataSasDeviceStatusChange_t ;

/* Variables and functions */
#define  MPI2_EVENT_SAS_DEV_STAT_RC_ABORT_TASK_SET_INTERNAL 140 
#define  MPI2_EVENT_SAS_DEV_STAT_RC_ASYNC_NOTIFICATION 139 
#define  MPI2_EVENT_SAS_DEV_STAT_RC_CLEAR_TASK_SET_INTERNAL 138 
#define  MPI2_EVENT_SAS_DEV_STAT_RC_CMP_EXPANDER_REDUCED_FUNCTIONALITY 137 
#define  MPI2_EVENT_SAS_DEV_STAT_RC_CMP_INTERNAL_DEV_RESET 136 
#define  MPI2_EVENT_SAS_DEV_STAT_RC_CMP_TASK_ABORT_INTERNAL 135 
#define  MPI2_EVENT_SAS_DEV_STAT_RC_EXPANDER_REDUCED_FUNCTIONALITY 134 
#define  MPI2_EVENT_SAS_DEV_STAT_RC_INTERNAL_DEVICE_RESET 133 
#define  MPI2_EVENT_SAS_DEV_STAT_RC_QUERY_TASK_INTERNAL 132 
#define  MPI2_EVENT_SAS_DEV_STAT_RC_SATA_INIT_FAILURE 131 
#define  MPI2_EVENT_SAS_DEV_STAT_RC_SMART_DATA 130 
#define  MPI2_EVENT_SAS_DEV_STAT_RC_TASK_ABORT_INTERNAL 129 
#define  MPI2_EVENT_SAS_DEV_STAT_RC_UNSUPPORTED 128 
 int /*<<< orphan*/  ioc_info (struct MPT3SAS_ADAPTER*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 

__attribute__((used)) static void
_scsih_sas_device_status_change_event_debug(struct MPT3SAS_ADAPTER *ioc,
	Mpi2EventDataSasDeviceStatusChange_t *event_data)
{
	char *reason_str = NULL;

	switch (event_data->ReasonCode) {
	case MPI2_EVENT_SAS_DEV_STAT_RC_SMART_DATA:
		reason_str = "smart data";
		break;
	case MPI2_EVENT_SAS_DEV_STAT_RC_UNSUPPORTED:
		reason_str = "unsupported device discovered";
		break;
	case MPI2_EVENT_SAS_DEV_STAT_RC_INTERNAL_DEVICE_RESET:
		reason_str = "internal device reset";
		break;
	case MPI2_EVENT_SAS_DEV_STAT_RC_TASK_ABORT_INTERNAL:
		reason_str = "internal task abort";
		break;
	case MPI2_EVENT_SAS_DEV_STAT_RC_ABORT_TASK_SET_INTERNAL:
		reason_str = "internal task abort set";
		break;
	case MPI2_EVENT_SAS_DEV_STAT_RC_CLEAR_TASK_SET_INTERNAL:
		reason_str = "internal clear task set";
		break;
	case MPI2_EVENT_SAS_DEV_STAT_RC_QUERY_TASK_INTERNAL:
		reason_str = "internal query task";
		break;
	case MPI2_EVENT_SAS_DEV_STAT_RC_SATA_INIT_FAILURE:
		reason_str = "sata init failure";
		break;
	case MPI2_EVENT_SAS_DEV_STAT_RC_CMP_INTERNAL_DEV_RESET:
		reason_str = "internal device reset complete";
		break;
	case MPI2_EVENT_SAS_DEV_STAT_RC_CMP_TASK_ABORT_INTERNAL:
		reason_str = "internal task abort complete";
		break;
	case MPI2_EVENT_SAS_DEV_STAT_RC_ASYNC_NOTIFICATION:
		reason_str = "internal async notification";
		break;
	case MPI2_EVENT_SAS_DEV_STAT_RC_EXPANDER_REDUCED_FUNCTIONALITY:
		reason_str = "expander reduced functionality";
		break;
	case MPI2_EVENT_SAS_DEV_STAT_RC_CMP_EXPANDER_REDUCED_FUNCTIONALITY:
		reason_str = "expander reduced functionality complete";
		break;
	default:
		reason_str = "unknown reason";
		break;
	}
	ioc_info(ioc, "device status change: (%s)\thandle(0x%04x), sas address(0x%016llx), tag(%d)",
		 reason_str, le16_to_cpu(event_data->DevHandle),
		 (u64)le64_to_cpu(event_data->SASAddress),
		 le16_to_cpu(event_data->TaskTag));
	if (event_data->ReasonCode == MPI2_EVENT_SAS_DEV_STAT_RC_SMART_DATA)
		pr_cont(", ASC(0x%x), ASCQ(0x%x)\n",
			event_data->ASC, event_data->ASCQ);
	pr_cont("\n");
}