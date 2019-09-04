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
typedef  int u16 ;
struct clk_mclk {int /*<<< orphan*/  is_mspro; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ U300_SYSCON_MMCR ; 
 int U300_SYSCON_MMCR_MMC_FB_CLK_SEL_ENABLE ; 
 int U300_SYSCON_MMCR_MSPRO_FREQSEL_ENABLE ; 
 scalar_t__ U300_SYSCON_MMF0R ; 
 int readw (scalar_t__) ; 
 scalar_t__ syscon_vbase ; 
 struct clk_mclk* to_mclk (struct clk_hw*) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int mclk_clk_prepare(struct clk_hw *hw)
{
	struct clk_mclk *mclk = to_mclk(hw);
	u16 val;

	/* The MMC and MSPRO clocks need some special set-up */
	if (!mclk->is_mspro) {
		/* Set default MMC clock divisor to 18.9 MHz */
		writew(0x0054U, syscon_vbase + U300_SYSCON_MMF0R);
		val = readw(syscon_vbase + U300_SYSCON_MMCR);
		/* Disable the MMC feedback clock */
		val &= ~U300_SYSCON_MMCR_MMC_FB_CLK_SEL_ENABLE;
		/* Disable MSPRO frequency */
		val &= ~U300_SYSCON_MMCR_MSPRO_FREQSEL_ENABLE;
		writew(val, syscon_vbase + U300_SYSCON_MMCR);
	} else {
		val = readw(syscon_vbase + U300_SYSCON_MMCR);
		/* Disable the MMC feedback clock */
		val &= ~U300_SYSCON_MMCR_MMC_FB_CLK_SEL_ENABLE;
		/* Enable MSPRO frequency */
		val |= U300_SYSCON_MMCR_MSPRO_FREQSEL_ENABLE;
		writew(val, syscon_vbase + U300_SYSCON_MMCR);
	}

	return 0;
}