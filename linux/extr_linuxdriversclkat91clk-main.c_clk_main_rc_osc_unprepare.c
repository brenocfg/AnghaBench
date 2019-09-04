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
struct regmap {int dummy; } ;
struct clk_main_rc_osc {struct regmap* regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_CKGR_MOR ; 
 int /*<<< orphan*/  AT91_PMC_KEY ; 
 unsigned int AT91_PMC_MOSCRCEN ; 
 unsigned int MOR_KEY_MASK ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 struct clk_main_rc_osc* to_clk_main_rc_osc (struct clk_hw*) ; 

__attribute__((used)) static void clk_main_rc_osc_unprepare(struct clk_hw *hw)
{
	struct clk_main_rc_osc *osc = to_clk_main_rc_osc(hw);
	struct regmap *regmap = osc->regmap;
	unsigned int mor;

	regmap_read(regmap, AT91_CKGR_MOR, &mor);

	if (!(mor & AT91_PMC_MOSCRCEN))
		return;

	regmap_update_bits(regmap, AT91_CKGR_MOR,
			   MOR_KEY_MASK | AT91_PMC_MOSCRCEN, AT91_PMC_KEY);
}