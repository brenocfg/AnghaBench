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
struct clk_regmap_mux_data {int /*<<< orphan*/  flags; } ;
struct clk_regmap {int dummy; } ;
struct clk_rate_request {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct clk_regmap_mux_data* clk_get_regmap_mux_data (struct clk_regmap*) ; 
 int clk_mux_determine_rate_flags (struct clk_hw*,struct clk_rate_request*,int /*<<< orphan*/ ) ; 
 struct clk_regmap* to_clk_regmap (struct clk_hw*) ; 

__attribute__((used)) static int clk_regmap_mux_determine_rate(struct clk_hw *hw,
					 struct clk_rate_request *req)
{
	struct clk_regmap *clk = to_clk_regmap(hw);
	struct clk_regmap_mux_data *mux = clk_get_regmap_mux_data(clk);

	return clk_mux_determine_rate_flags(hw, req, mux->flags);
}