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
typedef  int u16 ;
struct net_device {int dummy; } ;
struct hwrm_fw_reset_input {int /*<<< orphan*/  embedded_proc_type; void* selfrst_status; int /*<<< orphan*/  member_0; } ;
struct bnxt {int dummy; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
#define  BNXT_FW_RESET_AP 138 
#define  BNXT_FW_RESET_CHIP 137 
#define  BNX_DIR_TYPE_APE_FW 136 
#define  BNX_DIR_TYPE_APE_PATCH 135 
#define  BNX_DIR_TYPE_BONO_FW 134 
#define  BNX_DIR_TYPE_BONO_PATCH 133 
#define  BNX_DIR_TYPE_BOOTCODE 132 
#define  BNX_DIR_TYPE_BOOTCODE_2 131 
#define  BNX_DIR_TYPE_CHIMP_PATCH 130 
#define  BNX_DIR_TYPE_KONG_FW 129 
#define  BNX_DIR_TYPE_KONG_PATCH 128 
 int EACCES ; 
 int EINVAL ; 
 int /*<<< orphan*/  FW_RESET_REQ_EMBEDDED_PROC_TYPE_AP ; 
 int /*<<< orphan*/  FW_RESET_REQ_EMBEDDED_PROC_TYPE_BOOT ; 
 int /*<<< orphan*/  FW_RESET_REQ_EMBEDDED_PROC_TYPE_CHIP ; 
 int /*<<< orphan*/  FW_RESET_REQ_EMBEDDED_PROC_TYPE_MGMT ; 
 int /*<<< orphan*/  FW_RESET_REQ_EMBEDDED_PROC_TYPE_NETCTRL ; 
 int /*<<< orphan*/  FW_RESET_REQ_EMBEDDED_PROC_TYPE_ROCE ; 
 void* FW_RESET_REQ_SELFRST_STATUS_SELFRSTASAP ; 
 void* FW_RESET_REQ_SELFRST_STATUS_SELFRSTPCIERST ; 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_FW_RESET ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_fw_reset_input*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bnxt_print_admin_err (struct bnxt*) ; 
 int hwrm_send_message (struct bnxt*,struct hwrm_fw_reset_input*,int,int /*<<< orphan*/ ) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bnxt_firmware_reset(struct net_device *dev,
			       u16 dir_type)
{
	struct hwrm_fw_reset_input req = {0};
	struct bnxt *bp = netdev_priv(dev);
	int rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FW_RESET, -1, -1);

	/* TODO: Address self-reset of APE/KONG/BONO/TANG or ungraceful reset */
	/*       (e.g. when firmware isn't already running) */
	switch (dir_type) {
	case BNX_DIR_TYPE_CHIMP_PATCH:
	case BNX_DIR_TYPE_BOOTCODE:
	case BNX_DIR_TYPE_BOOTCODE_2:
		req.embedded_proc_type = FW_RESET_REQ_EMBEDDED_PROC_TYPE_BOOT;
		/* Self-reset ChiMP upon next PCIe reset: */
		req.selfrst_status = FW_RESET_REQ_SELFRST_STATUS_SELFRSTPCIERST;
		break;
	case BNX_DIR_TYPE_APE_FW:
	case BNX_DIR_TYPE_APE_PATCH:
		req.embedded_proc_type = FW_RESET_REQ_EMBEDDED_PROC_TYPE_MGMT;
		/* Self-reset APE upon next PCIe reset: */
		req.selfrst_status = FW_RESET_REQ_SELFRST_STATUS_SELFRSTPCIERST;
		break;
	case BNX_DIR_TYPE_KONG_FW:
	case BNX_DIR_TYPE_KONG_PATCH:
		req.embedded_proc_type =
			FW_RESET_REQ_EMBEDDED_PROC_TYPE_NETCTRL;
		break;
	case BNX_DIR_TYPE_BONO_FW:
	case BNX_DIR_TYPE_BONO_PATCH:
		req.embedded_proc_type = FW_RESET_REQ_EMBEDDED_PROC_TYPE_ROCE;
		break;
	case BNXT_FW_RESET_CHIP:
		req.embedded_proc_type = FW_RESET_REQ_EMBEDDED_PROC_TYPE_CHIP;
		req.selfrst_status = FW_RESET_REQ_SELFRST_STATUS_SELFRSTASAP;
		break;
	case BNXT_FW_RESET_AP:
		req.embedded_proc_type = FW_RESET_REQ_EMBEDDED_PROC_TYPE_AP;
		break;
	default:
		return -EINVAL;
	}

	rc = hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
	if (rc == -EACCES)
		bnxt_print_admin_err(bp);
	return rc;
}