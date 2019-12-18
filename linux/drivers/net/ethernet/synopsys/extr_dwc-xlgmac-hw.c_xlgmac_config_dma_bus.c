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
struct xlgmac_pdata {scalar_t__ mac_regs; } ;

/* Variables and functions */
 scalar_t__ DMA_SBMR ; 
 int /*<<< orphan*/  DMA_SBMR_BLEN_256_LEN ; 
 int /*<<< orphan*/  DMA_SBMR_BLEN_256_POS ; 
 int /*<<< orphan*/  DMA_SBMR_EAME_LEN ; 
 int /*<<< orphan*/  DMA_SBMR_EAME_POS ; 
 int /*<<< orphan*/  DMA_SBMR_UNDEF_LEN ; 
 int /*<<< orphan*/  DMA_SBMR_UNDEF_POS ; 
 int /*<<< orphan*/  XLGMAC_SET_REG_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void xlgmac_config_dma_bus(struct xlgmac_pdata *pdata)
{
	u32 regval;

	regval = readl(pdata->mac_regs + DMA_SBMR);
	/* Set enhanced addressing mode */
	regval = XLGMAC_SET_REG_BITS(regval, DMA_SBMR_EAME_POS,
				     DMA_SBMR_EAME_LEN, 1);
	/* Set the System Bus mode */
	regval = XLGMAC_SET_REG_BITS(regval, DMA_SBMR_UNDEF_POS,
				     DMA_SBMR_UNDEF_LEN, 1);
	regval = XLGMAC_SET_REG_BITS(regval, DMA_SBMR_BLEN_256_POS,
				     DMA_SBMR_BLEN_256_LEN, 1);
	writel(regval, pdata->mac_regs + DMA_SBMR);
}