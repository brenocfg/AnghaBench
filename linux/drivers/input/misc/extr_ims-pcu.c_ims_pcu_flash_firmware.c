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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct ims_pcu_flash_fmt {int /*<<< orphan*/  data; scalar_t__ len; int /*<<< orphan*/  addr; } ;
struct ims_pcu {int fw_start_addr; int fw_end_addr; unsigned int update_firmware_status; int /*<<< orphan*/  dev; int /*<<< orphan*/ * cmd_buf; } ;
struct ihex_binrec {int /*<<< orphan*/  data; int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
struct firmware {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERASE_APP ; 
 int IMS_PCU_CMD_RESPONSE_TIMEOUT ; 
 int /*<<< orphan*/  PROGRAM_COMPLETE ; 
 int /*<<< orphan*/  PROGRAM_DEVICE ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 struct ihex_binrec* ihex_next_binrec (struct ihex_binrec const*) ; 
 int ims_pcu_execute_bl_command (struct ims_pcu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int ims_pcu_verify_block (struct ims_pcu*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ims_pcu_flash_firmware(struct ims_pcu *pcu,
				  const struct firmware *fw,
				  unsigned int n_fw_records)
{
	const struct ihex_binrec *rec = (const struct ihex_binrec *)fw->data;
	struct ims_pcu_flash_fmt *fragment;
	unsigned int count = 0;
	u32 addr;
	u8 len;
	int error;

	error = ims_pcu_execute_bl_command(pcu, ERASE_APP, NULL, 0, 2000);
	if (error) {
		dev_err(pcu->dev,
			"Failed to erase application image, error: %d\n",
			error);
		return error;
	}

	while (rec) {
		/*
		 * The firmware format is messed up for some reason.
		 * The address twice that of what is needed for some
		 * reason and we end up overwriting half of the data
		 * with the next record.
		 */
		addr = be32_to_cpu(rec->addr) / 2;
		len = be16_to_cpu(rec->len);

		fragment = (void *)&pcu->cmd_buf[1];
		put_unaligned_le32(addr, &fragment->addr);
		fragment->len = len;
		memcpy(fragment->data, rec->data, len);

		error = ims_pcu_execute_bl_command(pcu, PROGRAM_DEVICE,
						NULL, len + 5,
						IMS_PCU_CMD_RESPONSE_TIMEOUT);
		if (error) {
			dev_err(pcu->dev,
				"Failed to write block at 0x%08x, len %d, error: %d\n",
				addr, len, error);
			return error;
		}

		if (addr >= pcu->fw_start_addr && addr < pcu->fw_end_addr) {
			error = ims_pcu_verify_block(pcu, addr, len, rec->data);
			if (error)
				return error;
		}

		count++;
		pcu->update_firmware_status = (count * 100) / n_fw_records;

		rec = ihex_next_binrec(rec);
	}

	error = ims_pcu_execute_bl_command(pcu, PROGRAM_COMPLETE,
					    NULL, 0, 2000);
	if (error)
		dev_err(pcu->dev,
			"Failed to send PROGRAM_COMPLETE, error: %d\n",
			error);

	return 0;
}