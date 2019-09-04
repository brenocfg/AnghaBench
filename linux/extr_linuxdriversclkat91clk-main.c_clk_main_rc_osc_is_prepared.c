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
 unsigned int AT91_PMC_MOSCRCEN ; 
 unsigned int AT91_PMC_MOSCRCS ; 
 int /*<<< orphan*/  AT91_PMC_SR ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 struct clk_main_rc_osc* to_clk_main_rc_osc (struct clk_hw*) ; 

__attribute__((used)) static int clk_main_rc_osc_is_prepared(struct clk_hw *hw)
{
	struct clk_main_rc_osc *osc = to_clk_main_rc_osc(hw);
	struct regmap *regmap = osc->regmap;
	unsigned int mor, status;

	regmap_read(regmap, AT91_CKGR_MOR, &mor);
	regmap_read(regmap, AT91_PMC_SR, &status);

	return (mor & AT91_PMC_MOSCRCEN) && (status & AT91_PMC_MOSCRCS);
}