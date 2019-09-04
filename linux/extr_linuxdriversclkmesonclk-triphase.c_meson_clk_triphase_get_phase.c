#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  width; } ;
struct meson_clk_triphase_data {TYPE_1__ ph0; } ;
struct clk_regmap {int /*<<< orphan*/  map; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int meson_clk_degrees_from_val (unsigned int,int /*<<< orphan*/ ) ; 
 struct meson_clk_triphase_data* meson_clk_triphase_data (struct clk_regmap*) ; 
 unsigned int meson_parm_read (int /*<<< orphan*/ ,TYPE_1__*) ; 
 struct clk_regmap* to_clk_regmap (struct clk_hw*) ; 

__attribute__((used)) static int meson_clk_triphase_get_phase(struct clk_hw *hw)
{
	struct clk_regmap *clk = to_clk_regmap(hw);
	struct meson_clk_triphase_data *tph = meson_clk_triphase_data(clk);
	unsigned int val;

	/* Phase are in sync, reading phase 0 is enough */
	val = meson_parm_read(clk->map, &tph->ph0);

	return meson_clk_degrees_from_val(val, tph->ph0.width);
}