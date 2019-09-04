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
struct nand_chip {int dummy; } ;
struct mtd_info {int dummy; } ;
struct denali_nand_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  denali_oob_xfer (struct mtd_info*,struct nand_chip*,int,int) ; 
 int /*<<< orphan*/  denali_reset_irq (struct denali_nand_info*) ; 
 struct denali_nand_info* mtd_to_denali (struct mtd_info*) ; 
 int nand_prog_page_end_op (struct nand_chip*) ; 

__attribute__((used)) static int denali_write_oob(struct mtd_info *mtd, struct nand_chip *chip,
			    int page)
{
	struct denali_nand_info *denali = mtd_to_denali(mtd);

	denali_reset_irq(denali);

	denali_oob_xfer(mtd, chip, page, 1);

	return nand_prog_page_end_op(chip);
}