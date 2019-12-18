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
struct qcom_nand_controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_ADDR0 ; 
 int /*<<< orphan*/  NAND_BAM_NEXT_SGL ; 
 int /*<<< orphan*/  NAND_DEV0_CFG0 ; 
 int /*<<< orphan*/  NAND_EBI2_ECC_BUF_CFG ; 
 int /*<<< orphan*/  write_reg_dma (struct qcom_nand_controller*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void config_nand_page_write(struct qcom_nand_controller *nandc)
{
	write_reg_dma(nandc, NAND_ADDR0, 2, 0);
	write_reg_dma(nandc, NAND_DEV0_CFG0, 3, 0);
	write_reg_dma(nandc, NAND_EBI2_ECC_BUF_CFG, 1,
		      NAND_BAM_NEXT_SGL);
}