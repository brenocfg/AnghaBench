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
struct mtd_info {int dummy; } ;
struct jz_nand {int is_reading; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  JZ_NAND_ECC_CTRL_ENABLE ; 
 int /*<<< orphan*/  JZ_NAND_ECC_CTRL_ENCODING ; 
 int /*<<< orphan*/  JZ_NAND_ECC_CTRL_RESET ; 
 int /*<<< orphan*/  JZ_NAND_ECC_CTRL_RS ; 
 scalar_t__ JZ_REG_NAND_ECC_CTRL ; 
 scalar_t__ JZ_REG_NAND_IRQ_STAT ; 
#define  NAND_ECC_READ 129 
#define  NAND_ECC_WRITE 128 
 struct jz_nand* mtd_to_jz_nand (struct mtd_info*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void jz_nand_hwctl(struct mtd_info *mtd, int mode)
{
	struct jz_nand *nand = mtd_to_jz_nand(mtd);
	uint32_t reg;

	writel(0, nand->base + JZ_REG_NAND_IRQ_STAT);
	reg = readl(nand->base + JZ_REG_NAND_ECC_CTRL);

	reg |= JZ_NAND_ECC_CTRL_RESET;
	reg |= JZ_NAND_ECC_CTRL_ENABLE;
	reg |= JZ_NAND_ECC_CTRL_RS;

	switch (mode) {
	case NAND_ECC_READ:
		reg &= ~JZ_NAND_ECC_CTRL_ENCODING;
		nand->is_reading = true;
		break;
	case NAND_ECC_WRITE:
		reg |= JZ_NAND_ECC_CTRL_ENCODING;
		nand->is_reading = false;
		break;
	default:
		break;
	}

	writel(reg, nand->base + JZ_REG_NAND_ECC_CTRL);
}