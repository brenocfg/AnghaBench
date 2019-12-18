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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ath6kl_usb_ctrl_diag_cmd_write {int /*<<< orphan*/  value; void* address; void* cmd; } ;
struct ath6kl_usb {scalar_t__ diag_cmd_buffer; } ;
struct ath6kl {struct ath6kl_usb* hif_priv; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_USB_CONTROL_REQ_DIAG_CMD ; 
 int /*<<< orphan*/  ATH6KL_USB_CTRL_DIAG_CC_WRITE ; 
 int ath6kl_usb_ctrl_msg_exchange (struct ath6kl_usb*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath6kl_warn (char*,int) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ath6kl_usb_ctrl_diag_cmd_write*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ath6kl_usb_diag_write32(struct ath6kl *ar, u32 address, __le32 data)
{
	struct ath6kl_usb *ar_usb = ar->hif_priv;
	struct ath6kl_usb_ctrl_diag_cmd_write *cmd;
	int ret;

	cmd = (struct ath6kl_usb_ctrl_diag_cmd_write *) ar_usb->diag_cmd_buffer;

	memset(cmd, 0, sizeof(struct ath6kl_usb_ctrl_diag_cmd_write));
	cmd->cmd = cpu_to_le32(ATH6KL_USB_CTRL_DIAG_CC_WRITE);
	cmd->address = cpu_to_le32(address);
	cmd->value = data;

	ret = ath6kl_usb_ctrl_msg_exchange(ar_usb,
					   ATH6KL_USB_CONTROL_REQ_DIAG_CMD,
					   (u8 *) cmd,
					   sizeof(*cmd),
					   0, NULL, NULL);
	if (ret) {
		ath6kl_warn("diag_write32 failed: %d\n", ret);
		return ret;
	}

	return 0;
}