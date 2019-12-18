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
struct davinci_nand_info {int core_chipsel; int is_readmode; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  NANDFCR_OFFSET ; 
 int /*<<< orphan*/  NAND_4BIT_ECC1_OFFSET ; 
 int NAND_ECC_READ ; 
 int /*<<< orphan*/  davinci_nand_lock ; 
 int davinci_nand_readl (struct davinci_nand_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  davinci_nand_writel (struct davinci_nand_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct davinci_nand_info* to_davinci_nand (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nand_davinci_hwctl_4bit(struct nand_chip *chip, int mode)
{
	struct davinci_nand_info *info = to_davinci_nand(nand_to_mtd(chip));
	unsigned long flags;
	u32 val;

	/* Reset ECC hardware */
	davinci_nand_readl(info, NAND_4BIT_ECC1_OFFSET);

	spin_lock_irqsave(&davinci_nand_lock, flags);

	/* Start 4-bit ECC calculation for read/write */
	val = davinci_nand_readl(info, NANDFCR_OFFSET);
	val &= ~(0x03 << 4);
	val |= (info->core_chipsel << 4) | BIT(12);
	davinci_nand_writel(info, NANDFCR_OFFSET, val);

	info->is_readmode = (mode == NAND_ECC_READ);

	spin_unlock_irqrestore(&davinci_nand_lock, flags);
}