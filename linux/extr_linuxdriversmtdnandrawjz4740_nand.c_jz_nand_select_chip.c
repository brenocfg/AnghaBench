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
typedef  int /*<<< orphan*/  uint32_t ;
struct nand_chip {int /*<<< orphan*/  IO_ADDR_W; int /*<<< orphan*/  IO_ADDR_R; } ;
struct mtd_info {int dummy; } ;
struct jz_nand {int* banks; int selected_bank; scalar_t__ base; int /*<<< orphan*/ * bank_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  JZ_NAND_CTRL_ASSERT_CHIP_MASK ; 
 scalar_t__ JZ_REG_NAND_CTRL ; 
 struct jz_nand* mtd_to_jz_nand (struct mtd_info*) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void jz_nand_select_chip(struct mtd_info *mtd, int chipnr)
{
	struct jz_nand *nand = mtd_to_jz_nand(mtd);
	struct nand_chip *chip = mtd_to_nand(mtd);
	uint32_t ctrl;
	int banknr;

	ctrl = readl(nand->base + JZ_REG_NAND_CTRL);
	ctrl &= ~JZ_NAND_CTRL_ASSERT_CHIP_MASK;

	if (chipnr == -1) {
		banknr = -1;
	} else {
		banknr = nand->banks[chipnr] - 1;
		chip->IO_ADDR_R = nand->bank_base[banknr];
		chip->IO_ADDR_W = nand->bank_base[banknr];
	}
	writel(ctrl, nand->base + JZ_REG_NAND_CTRL);

	nand->selected_bank = banknr;
}