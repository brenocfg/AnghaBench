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
struct resources {scalar_t__ gpmi_regs; scalar_t__ bch_regs; } ;
struct gpmi_nand_data {struct resources resources; } ;

/* Variables and functions */
 int /*<<< orphan*/  BM_GPMI_CTRL1_ATA_IRQRDY_POLARITY ; 
 int /*<<< orphan*/  BM_GPMI_CTRL1_BCH_MODE ; 
 int /*<<< orphan*/  BM_GPMI_CTRL1_DECOUPLE_CS ; 
 int /*<<< orphan*/  BM_GPMI_CTRL1_DEV_RESET ; 
 int /*<<< orphan*/  BM_GPMI_CTRL1_GPMI_MODE ; 
 int GPMI_IS_MXS (struct gpmi_nand_data*) ; 
 scalar_t__ HW_GPMI_CTRL1_CLR ; 
 scalar_t__ HW_GPMI_CTRL1_SET ; 
 int gpmi_reset_block (scalar_t__,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int gpmi_init(struct gpmi_nand_data *this)
{
	struct resources *r = &this->resources;
	int ret;

	ret = gpmi_reset_block(r->gpmi_regs, false);
	if (ret)
		goto err_out;

	/*
	 * Reset BCH here, too. We got failures otherwise :(
	 * See later BCH reset for explanation of MX23 and MX28 handling
	 */
	ret = gpmi_reset_block(r->bch_regs, GPMI_IS_MXS(this));
	if (ret)
		goto err_out;

	/* Choose NAND mode. */
	writel(BM_GPMI_CTRL1_GPMI_MODE, r->gpmi_regs + HW_GPMI_CTRL1_CLR);

	/* Set the IRQ polarity. */
	writel(BM_GPMI_CTRL1_ATA_IRQRDY_POLARITY,
				r->gpmi_regs + HW_GPMI_CTRL1_SET);

	/* Disable Write-Protection. */
	writel(BM_GPMI_CTRL1_DEV_RESET, r->gpmi_regs + HW_GPMI_CTRL1_SET);

	/* Select BCH ECC. */
	writel(BM_GPMI_CTRL1_BCH_MODE, r->gpmi_regs + HW_GPMI_CTRL1_SET);

	/*
	 * Decouple the chip select from dma channel. We use dma0 for all
	 * the chips.
	 */
	writel(BM_GPMI_CTRL1_DECOUPLE_CS, r->gpmi_regs + HW_GPMI_CTRL1_SET);

	return 0;
err_out:
	return ret;
}