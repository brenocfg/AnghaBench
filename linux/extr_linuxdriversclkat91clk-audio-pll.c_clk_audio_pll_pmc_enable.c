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
struct clk_audio_pmc {int /*<<< orphan*/  qdpmc; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_PMC_AUDIO_PLL0 ; 
 int AT91_PMC_AUDIO_PLL_PMCEN ; 
 int AT91_PMC_AUDIO_PLL_QDPMC (int /*<<< orphan*/ ) ; 
 int AT91_PMC_AUDIO_PLL_QDPMC_MASK ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct clk_audio_pmc* to_clk_audio_pmc (struct clk_hw*) ; 

__attribute__((used)) static int clk_audio_pll_pmc_enable(struct clk_hw *hw)
{
	struct clk_audio_pmc *apmc_ck = to_clk_audio_pmc(hw);

	regmap_update_bits(apmc_ck->regmap, AT91_PMC_AUDIO_PLL0,
			   AT91_PMC_AUDIO_PLL_PMCEN |
			   AT91_PMC_AUDIO_PLL_QDPMC_MASK,
			   AT91_PMC_AUDIO_PLL_PMCEN |
			   AT91_PMC_AUDIO_PLL_QDPMC(apmc_ck->qdpmc));
	return 0;
}