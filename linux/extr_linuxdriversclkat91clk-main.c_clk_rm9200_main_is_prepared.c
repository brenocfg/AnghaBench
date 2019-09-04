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
struct clk_rm9200_main {int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_CKGR_MCFR ; 
 unsigned int AT91_PMC_MAINRDY ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct clk_rm9200_main* to_clk_rm9200_main (struct clk_hw*) ; 

__attribute__((used)) static int clk_rm9200_main_is_prepared(struct clk_hw *hw)
{
	struct clk_rm9200_main *clkmain = to_clk_rm9200_main(hw);
	unsigned int status;

	regmap_read(clkmain->regmap, AT91_CKGR_MCFR, &status);

	return status & AT91_PMC_MAINRDY ? 1 : 0;
}