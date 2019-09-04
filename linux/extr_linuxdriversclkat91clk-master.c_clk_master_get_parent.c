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
struct clk_master {int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned int AT91_PMC_CSS ; 
 int /*<<< orphan*/  AT91_PMC_MCKR ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct clk_master* to_clk_master (struct clk_hw*) ; 

__attribute__((used)) static u8 clk_master_get_parent(struct clk_hw *hw)
{
	struct clk_master *master = to_clk_master(hw);
	unsigned int mckr;

	regmap_read(master->regmap, AT91_PMC_MCKR, &mckr);

	return mckr & AT91_PMC_CSS;
}