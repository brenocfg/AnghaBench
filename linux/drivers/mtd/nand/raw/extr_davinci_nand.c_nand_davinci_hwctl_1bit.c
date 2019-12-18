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
struct nand_chip {int dummy; } ;
struct davinci_nand_info {scalar_t__ core_chipsel; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (scalar_t__) ; 
 int /*<<< orphan*/  NANDFCR_OFFSET ; 
 int /*<<< orphan*/  davinci_nand_lock ; 
 int /*<<< orphan*/  davinci_nand_readl (struct davinci_nand_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  davinci_nand_writel (struct davinci_nand_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_davinci_readecc_1bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct davinci_nand_info* to_davinci_nand (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nand_davinci_hwctl_1bit(struct nand_chip *chip, int mode)
{
	struct davinci_nand_info *info;
	uint32_t nandcfr;
	unsigned long flags;

	info = to_davinci_nand(nand_to_mtd(chip));

	/* Reset ECC hardware */
	nand_davinci_readecc_1bit(nand_to_mtd(chip));

	spin_lock_irqsave(&davinci_nand_lock, flags);

	/* Restart ECC hardware */
	nandcfr = davinci_nand_readl(info, NANDFCR_OFFSET);
	nandcfr |= BIT(8 + info->core_chipsel);
	davinci_nand_writel(info, NANDFCR_OFFSET, nandcfr);

	spin_unlock_irqrestore(&davinci_nand_lock, flags);
}