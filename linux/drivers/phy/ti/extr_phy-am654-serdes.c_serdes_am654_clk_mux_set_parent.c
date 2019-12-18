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
typedef  size_t u32 ;
struct serdes_am654_clk_mux {unsigned int reg; int clk_id; struct regmap* regmap; } ;
struct regmap {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 size_t AM654_SERDES_CTRL_CLKSEL_MASK ; 
 size_t AM654_SERDES_CTRL_CLKSEL_SHIFT ; 
 int EINVAL ; 
 int SERDES_NUM_CLOCKS ; 
 size_t SERDES_NUM_MUX_COMBINATIONS ; 
 int /*<<< orphan*/  WARN (int,char*,char const*) ; 
 char* clk_hw_get_name (struct clk_hw*) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,unsigned int,size_t*) ; 
 int regmap_update_bits (struct regmap*,unsigned int,size_t,size_t) ; 
 int** serdes_am654_mux_table ; 
 struct serdes_am654_clk_mux* to_serdes_am654_clk_mux (struct clk_hw*) ; 

__attribute__((used)) static int serdes_am654_clk_mux_set_parent(struct clk_hw *hw, u8 index)
{
	struct serdes_am654_clk_mux *mux = to_serdes_am654_clk_mux(hw);
	struct regmap *regmap = mux->regmap;
	const char *name = clk_hw_get_name(hw);
	unsigned int reg = mux->reg;
	int clk_id = mux->clk_id;
	int parents[SERDES_NUM_CLOCKS];
	const int *p;
	u32 val;
	int found, i;
	int ret;

	/* get existing setting */
	regmap_read(regmap, reg, &val);
	val &= AM654_SERDES_CTRL_CLKSEL_MASK;
	val >>= AM654_SERDES_CTRL_CLKSEL_SHIFT;

	for (i = 0; i < SERDES_NUM_CLOCKS; i++)
		parents[i] = serdes_am654_mux_table[val][i];

	/* change parent of this clock. others left intact */
	parents[clk_id] = index;

	/* Find the match */
	for (val = 0; val < SERDES_NUM_MUX_COMBINATIONS; val++) {
		p = serdes_am654_mux_table[val];
		found = 1;
		for (i = 0; i < SERDES_NUM_CLOCKS; i++) {
			if (parents[i] != p[i]) {
				found = 0;
				break;
			}
		}

		if (found)
			break;
	}

	if (!found) {
		/*
		 * This can never happen, unless we missed
		 * a valid combination in serdes_am654_mux_table.
		 */
		WARN(1, "Failed to find the parent of %s clock\n", name);
		return -EINVAL;
	}

	val <<= AM654_SERDES_CTRL_CLKSEL_SHIFT;
	ret = regmap_update_bits(regmap, reg, AM654_SERDES_CTRL_CLKSEL_MASK,
				 val);

	return ret;
}