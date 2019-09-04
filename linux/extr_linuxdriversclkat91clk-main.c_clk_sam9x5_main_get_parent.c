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
typedef  int u8 ;
struct clk_sam9x5_main {int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_CKGR_MOR ; 
 unsigned int AT91_PMC_MOSCEN ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct clk_sam9x5_main* to_clk_sam9x5_main (struct clk_hw*) ; 

__attribute__((used)) static u8 clk_sam9x5_main_get_parent(struct clk_hw *hw)
{
	struct clk_sam9x5_main *clkmain = to_clk_sam9x5_main(hw);
	unsigned int status;

	regmap_read(clkmain->regmap, AT91_CKGR_MOR, &status);

	return status & AT91_PMC_MOSCEN ? 1 : 0;
}