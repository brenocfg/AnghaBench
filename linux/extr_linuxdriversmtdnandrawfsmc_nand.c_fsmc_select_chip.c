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
struct mtd_info {int dummy; } ;
struct fsmc_nand_data {scalar_t__ regs_va; } ;

/* Variables and functions */
 int FSMC_ENABLE ; 
 scalar_t__ FSMC_PC ; 
 int /*<<< orphan*/  mb () ; 
 struct fsmc_nand_data* mtd_to_fsmc (struct mtd_info*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void fsmc_select_chip(struct mtd_info *mtd, int chipnr)
{
	struct fsmc_nand_data *host = mtd_to_fsmc(mtd);
	u32 pc;

	/* Support only one CS */
	if (chipnr > 0)
		return;

	pc = readl(host->regs_va + FSMC_PC);
	if (chipnr < 0)
		writel_relaxed(pc & ~FSMC_ENABLE, host->regs_va + FSMC_PC);
	else
		writel_relaxed(pc | FSMC_ENABLE, host->regs_va + FSMC_PC);

	/* nCE line must be asserted before starting any operation */
	mb();
}