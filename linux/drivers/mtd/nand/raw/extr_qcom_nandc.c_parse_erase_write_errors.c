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
typedef  int u32 ;
struct nand_ecc_ctrl {int steps; } ;
struct nand_chip {struct nand_ecc_ctrl ecc; } ;
struct qcom_nand_host {int /*<<< orphan*/  status; struct nand_chip chip; } ;
struct qcom_nand_controller {int /*<<< orphan*/ * reg_read_buf; } ;

/* Variables and functions */
 int FS_DEVICE_STS_ERR ; 
 int FS_MPU_ERR ; 
 int FS_OP_ERR ; 
 int NAND_CMD_PAGEPROG ; 
 int /*<<< orphan*/  NAND_STATUS_FAIL ; 
 int /*<<< orphan*/  NAND_STATUS_WP ; 
 struct qcom_nand_controller* get_qcom_nand_controller (struct nand_chip*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nandc_read_buffer_sync (struct qcom_nand_controller*,int) ; 

__attribute__((used)) static void parse_erase_write_errors(struct qcom_nand_host *host, int command)
{
	struct nand_chip *chip = &host->chip;
	struct qcom_nand_controller *nandc = get_qcom_nand_controller(chip);
	struct nand_ecc_ctrl *ecc = &chip->ecc;
	int num_cw;
	int i;

	num_cw = command == NAND_CMD_PAGEPROG ? ecc->steps : 1;
	nandc_read_buffer_sync(nandc, true);

	for (i = 0; i < num_cw; i++) {
		u32 flash_status = le32_to_cpu(nandc->reg_read_buf[i]);

		if (flash_status & FS_MPU_ERR)
			host->status &= ~NAND_STATUS_WP;

		if (flash_status & FS_OP_ERR || (i == (num_cw - 1) &&
						 (flash_status &
						  FS_DEVICE_STS_ERR)))
			host->status |= NAND_STATUS_FAIL;
	}
}