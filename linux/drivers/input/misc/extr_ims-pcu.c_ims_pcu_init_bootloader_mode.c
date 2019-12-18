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
struct ims_pcu {int /*<<< orphan*/  async_firmware_done; int /*<<< orphan*/  dev; void* fw_end_addr; void* fw_start_addr; int /*<<< orphan*/ * cmd_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IMS_PCU_CMD_RESPONSE_TIMEOUT ; 
 int IMS_PCU_DATA_OFFSET ; 
 int /*<<< orphan*/  IMS_PCU_FIRMWARE_NAME ; 
 int /*<<< orphan*/  QUERY_DEVICE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,void*,void*) ; 
 void* get_unaligned_le32 (int /*<<< orphan*/ *) ; 
 int ims_pcu_execute_bl_command (struct ims_pcu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ims_pcu_process_async_firmware ; 
 int request_firmware_nowait (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ims_pcu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ims_pcu_init_bootloader_mode(struct ims_pcu *pcu)
{
	int error;

	error = ims_pcu_execute_bl_command(pcu, QUERY_DEVICE, NULL, 0,
					   IMS_PCU_CMD_RESPONSE_TIMEOUT);
	if (error) {
		dev_err(pcu->dev, "Bootloader does not respond, aborting\n");
		return error;
	}

	pcu->fw_start_addr =
		get_unaligned_le32(&pcu->cmd_buf[IMS_PCU_DATA_OFFSET + 11]);
	pcu->fw_end_addr =
		get_unaligned_le32(&pcu->cmd_buf[IMS_PCU_DATA_OFFSET + 15]);

	dev_info(pcu->dev,
		 "Device is in bootloader mode (addr 0x%08x-0x%08x), requesting firmware\n",
		 pcu->fw_start_addr, pcu->fw_end_addr);

	error = request_firmware_nowait(THIS_MODULE, true,
					IMS_PCU_FIRMWARE_NAME,
					pcu->dev, GFP_KERNEL, pcu,
					ims_pcu_process_async_firmware);
	if (error) {
		/* This error is not fatal, let userspace have another chance */
		complete(&pcu->async_firmware_done);
	}

	return 0;
}