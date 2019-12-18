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
struct ingenic_ecc {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  JZ_NAND_ECC_CTRL_ENABLE ; 
 int /*<<< orphan*/  JZ_NAND_ECC_CTRL_ENCODING ; 
 int /*<<< orphan*/  JZ_NAND_ECC_CTRL_RESET ; 
 int /*<<< orphan*/  JZ_NAND_ECC_CTRL_RS ; 
 scalar_t__ JZ_REG_NAND_ECC_CTRL ; 
 scalar_t__ JZ_REG_NAND_IRQ_STAT ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void jz4740_ecc_reset(struct ingenic_ecc *ecc, bool calc_ecc)
{
	uint32_t reg;

	/* Clear interrupt status */
	writel(0, ecc->base + JZ_REG_NAND_IRQ_STAT);

	/* Initialize and enable ECC hardware */
	reg = readl(ecc->base + JZ_REG_NAND_ECC_CTRL);
	reg |= JZ_NAND_ECC_CTRL_RESET;
	reg |= JZ_NAND_ECC_CTRL_ENABLE;
	reg |= JZ_NAND_ECC_CTRL_RS;
	if (calc_ecc) /* calculate ECC from data */
		reg |= JZ_NAND_ECC_CTRL_ENCODING;
	else /* correct data from ECC */
		reg &= ~JZ_NAND_ECC_CTRL_ENCODING;

	writel(reg, ecc->base + JZ_REG_NAND_ECC_CTRL);
}