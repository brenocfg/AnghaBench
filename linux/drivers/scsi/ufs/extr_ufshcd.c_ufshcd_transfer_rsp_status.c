#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ufshcd_lrb {int task_tag; int /*<<< orphan*/  ucd_rsp_ptr; } ;
struct TYPE_2__ {int /*<<< orphan*/  last_hibern8_exit_tstamp; } ;
struct ufs_hba {int /*<<< orphan*/  dev; int /*<<< orphan*/  eeh_work; int /*<<< orphan*/  pm_op_in_progress; TYPE_1__ ufs_stats; } ;

/* Variables and functions */
 int DID_ABORT ; 
 int DID_ERROR ; 
 scalar_t__ DID_OK ; 
 int DID_REQUEUE ; 
 int MASK_SCSI_STATUS ; 
#define  OCS_ABORTED 138 
#define  OCS_FATAL_ERROR 137 
#define  OCS_INVALID_CMD_TABLE_ATTR 136 
#define  OCS_INVALID_COMMAND_STATUS 135 
#define  OCS_INVALID_PRDT_ATTR 134 
#define  OCS_MISMATCH_DATA_BUF_SIZE 133 
#define  OCS_MISMATCH_RESP_UPIU_SIZE 132 
#define  OCS_PEER_COMM_FAILURE 131 
#define  OCS_SUCCESS 130 
#define  UPIU_TRANSACTION_REJECT_UPIU 129 
#define  UPIU_TRANSACTION_RESPONSE 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ host_byte (int) ; 
 int /*<<< orphan*/  ktime_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int ufshcd_get_req_rsp (int /*<<< orphan*/ ) ; 
 int ufshcd_get_rsp_upiu_result (int /*<<< orphan*/ ) ; 
 int ufshcd_get_tr_ocs (struct ufshcd_lrb*) ; 
 int /*<<< orphan*/  ufshcd_is_exception_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufshcd_print_host_regs (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_print_host_state (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_print_trs (struct ufs_hba*,int,int) ; 
 int ufshcd_scsi_cmd_status (struct ufshcd_lrb*,int) ; 

__attribute__((used)) static inline int
ufshcd_transfer_rsp_status(struct ufs_hba *hba, struct ufshcd_lrb *lrbp)
{
	int result = 0;
	int scsi_status;
	int ocs;

	/* overall command status of utrd */
	ocs = ufshcd_get_tr_ocs(lrbp);

	switch (ocs) {
	case OCS_SUCCESS:
		result = ufshcd_get_req_rsp(lrbp->ucd_rsp_ptr);
		hba->ufs_stats.last_hibern8_exit_tstamp = ktime_set(0, 0);
		switch (result) {
		case UPIU_TRANSACTION_RESPONSE:
			/*
			 * get the response UPIU result to extract
			 * the SCSI command status
			 */
			result = ufshcd_get_rsp_upiu_result(lrbp->ucd_rsp_ptr);

			/*
			 * get the result based on SCSI status response
			 * to notify the SCSI midlayer of the command status
			 */
			scsi_status = result & MASK_SCSI_STATUS;
			result = ufshcd_scsi_cmd_status(lrbp, scsi_status);

			/*
			 * Currently we are only supporting BKOPs exception
			 * events hence we can ignore BKOPs exception event
			 * during power management callbacks. BKOPs exception
			 * event is not expected to be raised in runtime suspend
			 * callback as it allows the urgent bkops.
			 * During system suspend, we are anyway forcefully
			 * disabling the bkops and if urgent bkops is needed
			 * it will be enabled on system resume. Long term
			 * solution could be to abort the system suspend if
			 * UFS device needs urgent BKOPs.
			 */
			if (!hba->pm_op_in_progress &&
			    ufshcd_is_exception_event(lrbp->ucd_rsp_ptr))
				schedule_work(&hba->eeh_work);
			break;
		case UPIU_TRANSACTION_REJECT_UPIU:
			/* TODO: handle Reject UPIU Response */
			result = DID_ERROR << 16;
			dev_err(hba->dev,
				"Reject UPIU not fully implemented\n");
			break;
		default:
			dev_err(hba->dev,
				"Unexpected request response code = %x\n",
				result);
			result = DID_ERROR << 16;
			break;
		}
		break;
	case OCS_ABORTED:
		result |= DID_ABORT << 16;
		break;
	case OCS_INVALID_COMMAND_STATUS:
		result |= DID_REQUEUE << 16;
		break;
	case OCS_INVALID_CMD_TABLE_ATTR:
	case OCS_INVALID_PRDT_ATTR:
	case OCS_MISMATCH_DATA_BUF_SIZE:
	case OCS_MISMATCH_RESP_UPIU_SIZE:
	case OCS_PEER_COMM_FAILURE:
	case OCS_FATAL_ERROR:
	default:
		result |= DID_ERROR << 16;
		dev_err(hba->dev,
				"OCS error from controller = %x for tag %d\n",
				ocs, lrbp->task_tag);
		ufshcd_print_host_regs(hba);
		ufshcd_print_host_state(hba);
		break;
	} /* end of switch */

	if (host_byte(result) != DID_OK)
		ufshcd_print_trs(hba, 1 << lrbp->task_tag, true);
	return result;
}