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
struct clk_hw {int dummy; } ;
struct clk_audio_frac {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_PMC_AUDIO_PLL0 ; 
 int /*<<< orphan*/  AT91_PMC_AUDIO_PLL_PLLEN ; 
 int /*<<< orphan*/  AT91_PMC_AUDIO_PLL_RESETN ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk_audio_frac* to_clk_audio_frac (struct clk_hw*) ; 

__attribute__((used)) static void clk_audio_pll_frac_disable(struct clk_hw *hw)
{
	struct clk_audio_frac *frac = to_clk_audio_frac(hw);

	regmap_update_bits(frac->regmap, AT91_PMC_AUDIO_PLL0,
			   AT91_PMC_AUDIO_PLL_PLLEN, 0);
	/* do it in 2 separated writes */
	regmap_update_bits(frac->regmap, AT91_PMC_AUDIO_PLL0,
			   AT91_PMC_AUDIO_PLL_RESETN, 0);
}