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
struct ql_adapter {int /*<<< orphan*/  ndev; } ;
struct mbox_params {int out_count; int* mbox_out; int /*<<< orphan*/ * mbox_in; } ;

/* Variables and functions */
#define  AEN_AEN_LOST 146 
#define  AEN_AEN_SFP_IN 145 
#define  AEN_AEN_SFP_OUT 144 
#define  AEN_DCBX_CHG 143 
#define  AEN_FW_INIT_DONE 142 
#define  AEN_FW_INIT_FAIL 141 
#define  AEN_IDC_CMPLT 140 
#define  AEN_IDC_EXT 139 
#define  AEN_IDC_REQ 138 
#define  AEN_LINK_DOWN 137 
#define  AEN_LINK_UP 136 
#define  AEN_SYS_ERR 135 
 int /*<<< orphan*/  CSR ; 
 int /*<<< orphan*/  CSR_CMD_CLR_R2PCI_INT ; 
 int EIO ; 
 int /*<<< orphan*/  MB_CMD_EX_FW ; 
#define  MB_CMD_STS_CSUM_ERR 134 
#define  MB_CMD_STS_ERR 133 
#define  MB_CMD_STS_GOOD 132 
#define  MB_CMD_STS_INTRMDT 131 
#define  MB_CMD_STS_INVLD_CMD 130 
#define  MB_CMD_STS_PARAM_ERR 129 
#define  MB_CMD_STS_XFC_ERR 128 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ql_aen_lost (struct ql_adapter*,struct mbox_params*) ; 
 int ql_get_mb_sts (struct ql_adapter*,struct mbox_params*) ; 
 int ql_idc_cmplt_aen (struct ql_adapter*) ; 
 int ql_idc_req_aen (struct ql_adapter*) ; 
 int /*<<< orphan*/  ql_init_fw_done (struct ql_adapter*,struct mbox_params*) ; 
 int /*<<< orphan*/  ql_link_down (struct ql_adapter*,struct mbox_params*) ; 
 int /*<<< orphan*/  ql_link_up (struct ql_adapter*,struct mbox_params*) ; 
 int /*<<< orphan*/  ql_queue_asic_error (struct ql_adapter*) ; 
 int /*<<< orphan*/  ql_queue_fw_error (struct ql_adapter*) ; 
 int /*<<< orphan*/  ql_sfp_in (struct ql_adapter*,struct mbox_params*) ; 
 int /*<<< orphan*/  ql_sfp_out (struct ql_adapter*,struct mbox_params*) ; 
 int /*<<< orphan*/  ql_write32 (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ql_mpi_handler(struct ql_adapter *qdev, struct mbox_params *mbcp)
{
	int status;
	int orig_count = mbcp->out_count;

	/* Just get mailbox zero for now. */
	mbcp->out_count = 1;
	status = ql_get_mb_sts(qdev, mbcp);
	if (status) {
		netif_err(qdev, drv, qdev->ndev,
			  "Could not read MPI, resetting ASIC!\n");
		ql_queue_asic_error(qdev);
		goto end;
	}

	switch (mbcp->mbox_out[0]) {

	/* This case is only active when we arrive here
	 * as a result of issuing a mailbox command to
	 * the firmware.
	 */
	case MB_CMD_STS_INTRMDT:
	case MB_CMD_STS_GOOD:
	case MB_CMD_STS_INVLD_CMD:
	case MB_CMD_STS_XFC_ERR:
	case MB_CMD_STS_CSUM_ERR:
	case MB_CMD_STS_ERR:
	case MB_CMD_STS_PARAM_ERR:
		/* We can only get mailbox status if we're polling from an
		 * unfinished command.  Get the rest of the status data and
		 * return back to the caller.
		 * We only end up here when we're polling for a mailbox
		 * command completion.
		 */
		mbcp->out_count = orig_count;
		status = ql_get_mb_sts(qdev, mbcp);
		return status;

	/* We are being asked by firmware to accept
	 * a change to the port.  This is only
	 * a change to max frame sizes (Tx/Rx), pause
	 * parameters, or loopback mode.
	 */
	case AEN_IDC_REQ:
		status = ql_idc_req_aen(qdev);
		break;

	/* Process and inbound IDC event.
	 * This will happen when we're trying to
	 * change tx/rx max frame size, change pause
	 * parameters or loopback mode.
	 */
	case AEN_IDC_CMPLT:
	case AEN_IDC_EXT:
		status = ql_idc_cmplt_aen(qdev);
		break;

	case AEN_LINK_UP:
		ql_link_up(qdev, mbcp);
		break;

	case AEN_LINK_DOWN:
		ql_link_down(qdev, mbcp);
		break;

	case AEN_FW_INIT_DONE:
		/* If we're in process on executing the firmware,
		 * then convert the status to normal mailbox status.
		 */
		if (mbcp->mbox_in[0] == MB_CMD_EX_FW) {
			mbcp->out_count = orig_count;
			status = ql_get_mb_sts(qdev, mbcp);
			mbcp->mbox_out[0] = MB_CMD_STS_GOOD;
			return status;
		}
		ql_init_fw_done(qdev, mbcp);
		break;

	case AEN_AEN_SFP_IN:
		ql_sfp_in(qdev, mbcp);
		break;

	case AEN_AEN_SFP_OUT:
		ql_sfp_out(qdev, mbcp);
		break;

	/* This event can arrive at boot time or after an
	 * MPI reset if the firmware failed to initialize.
	 */
	case AEN_FW_INIT_FAIL:
		/* If we're in process on executing the firmware,
		 * then convert the status to normal mailbox status.
		 */
		if (mbcp->mbox_in[0] == MB_CMD_EX_FW) {
			mbcp->out_count = orig_count;
			status = ql_get_mb_sts(qdev, mbcp);
			mbcp->mbox_out[0] = MB_CMD_STS_ERR;
			return status;
		}
		netif_err(qdev, drv, qdev->ndev,
			  "Firmware initialization failed.\n");
		status = -EIO;
		ql_queue_fw_error(qdev);
		break;

	case AEN_SYS_ERR:
		netif_err(qdev, drv, qdev->ndev, "System Error.\n");
		ql_queue_fw_error(qdev);
		status = -EIO;
		break;

	case AEN_AEN_LOST:
		ql_aen_lost(qdev, mbcp);
		break;

	case AEN_DCBX_CHG:
		/* Need to support AEN 8110 */
		break;
	default:
		netif_err(qdev, drv, qdev->ndev,
			  "Unsupported AE %.08x.\n", mbcp->mbox_out[0]);
		/* Clear the MPI firmware status. */
	}
end:
	ql_write32(qdev, CSR, CSR_CMD_CLR_R2PCI_INT);
	/* Restore the original mailbox count to
	 * what the caller asked for.  This can get
	 * changed when a mailbox command is waiting
	 * for a response and an AEN arrives and
	 * is handled.
	 * */
	mbcp->out_count = orig_count;
	return status;
}