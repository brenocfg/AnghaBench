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
struct of_phandle_args {int args_count; scalar_t__* args; } ;
struct clk_muxing_ctrl {int num_muxes; struct clk** muxes; } ;
struct clk_mux {scalar_t__ shift; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 struct clk* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __clk_get_hw (struct clk*) ; 
 struct clk_mux* to_clk_mux (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct clk *clk_muxing_get_src(
	struct of_phandle_args *clkspec, void *data)
{
	struct clk_muxing_ctrl *ctrl = (struct clk_muxing_ctrl *)data;
	int n;

	if (clkspec->args_count < 1)
		return ERR_PTR(-EINVAL);

	for (n = 0; n < ctrl->num_muxes; n++) {
		struct clk_mux *mux =
			to_clk_mux(__clk_get_hw(ctrl->muxes[n]));
		if (clkspec->args[0] == mux->shift)
			return ctrl->muxes[n];
	}
	return ERR_PTR(-ENODEV);
}