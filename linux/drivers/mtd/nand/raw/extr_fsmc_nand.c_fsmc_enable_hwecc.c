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
struct fsmc_nand_data {scalar_t__ regs_va; } ;

/* Variables and functions */
 int FSMC_ECCEN ; 
 int FSMC_ECCPLEN_256 ; 
 scalar_t__ FSMC_PC ; 
 struct fsmc_nand_data* nand_to_fsmc (struct nand_chip*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void fsmc_enable_hwecc(struct nand_chip *chip, int mode)
{
	struct fsmc_nand_data *host = nand_to_fsmc(chip);

	writel_relaxed(readl(host->regs_va + FSMC_PC) & ~FSMC_ECCPLEN_256,
		       host->regs_va + FSMC_PC);
	writel_relaxed(readl(host->regs_va + FSMC_PC) & ~FSMC_ECCEN,
		       host->regs_va + FSMC_PC);
	writel_relaxed(readl(host->regs_va + FSMC_PC) | FSMC_ECCEN,
		       host->regs_va + FSMC_PC);
}