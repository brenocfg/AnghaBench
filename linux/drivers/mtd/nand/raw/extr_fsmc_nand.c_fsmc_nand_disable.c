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
typedef  int /*<<< orphan*/  u32 ;
struct fsmc_nand_data {scalar_t__ regs_va; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSMC_ENABLE ; 
 scalar_t__ FSMC_PC ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void fsmc_nand_disable(struct fsmc_nand_data *host)
{
	u32 val;

	val = readl(host->regs_va + FSMC_PC);
	val &= ~FSMC_ENABLE;
	writel(val, host->regs_va + FSMC_PC);
}