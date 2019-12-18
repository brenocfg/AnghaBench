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
struct nand_chip {int dummy; } ;
struct qcom_nand_host {struct nand_chip chip; } ;
struct qcom_nand_controller {int /*<<< orphan*/ * reg_read_buf; } ;

/* Variables and functions */
 int EIO ; 
 int FS_MPU_ERR ; 
 int FS_OP_ERR ; 
 struct qcom_nand_controller* get_qcom_nand_controller (struct nand_chip*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_flash_errors(struct qcom_nand_host *host, int cw_cnt)
{
	struct nand_chip *chip = &host->chip;
	struct qcom_nand_controller *nandc = get_qcom_nand_controller(chip);
	int i;

	for (i = 0; i < cw_cnt; i++) {
		u32 flash = le32_to_cpu(nandc->reg_read_buf[i]);

		if (flash & (FS_OP_ERR | FS_MPU_ERR))
			return -EIO;
	}

	return 0;
}