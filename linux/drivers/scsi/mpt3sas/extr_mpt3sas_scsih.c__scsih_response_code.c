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
typedef  int u8 ;
struct MPT3SAS_ADAPTER {int dummy; } ;

/* Variables and functions */
#define  MPI2_SCSITASKMGMT_RSP_INVALID_FRAME 134 
#define  MPI2_SCSITASKMGMT_RSP_IO_QUEUED_ON_IOC 133 
#define  MPI2_SCSITASKMGMT_RSP_TM_COMPLETE 132 
#define  MPI2_SCSITASKMGMT_RSP_TM_FAILED 131 
#define  MPI2_SCSITASKMGMT_RSP_TM_INVALID_LUN 130 
#define  MPI2_SCSITASKMGMT_RSP_TM_NOT_SUPPORTED 129 
#define  MPI2_SCSITASKMGMT_RSP_TM_SUCCEEDED 128 
 int /*<<< orphan*/  ioc_warn (struct MPT3SAS_ADAPTER*,char*,int,char*) ; 

__attribute__((used)) static void
_scsih_response_code(struct MPT3SAS_ADAPTER *ioc, u8 response_code)
{
	char *desc;

	switch (response_code) {
	case MPI2_SCSITASKMGMT_RSP_TM_COMPLETE:
		desc = "task management request completed";
		break;
	case MPI2_SCSITASKMGMT_RSP_INVALID_FRAME:
		desc = "invalid frame";
		break;
	case MPI2_SCSITASKMGMT_RSP_TM_NOT_SUPPORTED:
		desc = "task management request not supported";
		break;
	case MPI2_SCSITASKMGMT_RSP_TM_FAILED:
		desc = "task management request failed";
		break;
	case MPI2_SCSITASKMGMT_RSP_TM_SUCCEEDED:
		desc = "task management request succeeded";
		break;
	case MPI2_SCSITASKMGMT_RSP_TM_INVALID_LUN:
		desc = "invalid lun";
		break;
	case 0xA:
		desc = "overlapped tag attempted";
		break;
	case MPI2_SCSITASKMGMT_RSP_IO_QUEUED_ON_IOC:
		desc = "task queued, however not sent to target";
		break;
	default:
		desc = "unknown";
		break;
	}
	ioc_warn(ioc, "response_code(0x%01x): %s\n", response_code, desc);
}