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
typedef  unsigned int u8 ;
struct clk_hw {int dummy; } ;
struct at91sam9x5_clk_smd {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_PMC_SMD ; 
 unsigned int AT91_PMC_SMDS ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct at91sam9x5_clk_smd* to_at91sam9x5_clk_smd (struct clk_hw*) ; 

__attribute__((used)) static u8 at91sam9x5_clk_smd_get_parent(struct clk_hw *hw)
{
	struct at91sam9x5_clk_smd *smd = to_at91sam9x5_clk_smd(hw);
	unsigned int smdr;

	regmap_read(smd->regmap, AT91_PMC_SMD, &smdr);

	return smdr & AT91_PMC_SMDS;
}