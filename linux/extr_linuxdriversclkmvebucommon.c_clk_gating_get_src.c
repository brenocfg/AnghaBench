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
struct of_phandle_args {int args_count; scalar_t__* args; } ;
struct clk_gate {scalar_t__ bit_idx; } ;
struct clk {int dummy; } ;
struct TYPE_2__ {int num_gates; struct clk** gates; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 struct clk* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __clk_get_hw (struct clk*) ; 
 TYPE_1__* ctrl ; 
 struct clk_gate* to_clk_gate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct clk *clk_gating_get_src(
	struct of_phandle_args *clkspec, void *data)
{
	int n;

	if (clkspec->args_count < 1)
		return ERR_PTR(-EINVAL);

	for (n = 0; n < ctrl->num_gates; n++) {
		struct clk_gate *gate =
			to_clk_gate(__clk_get_hw(ctrl->gates[n]));
		if (clkspec->args[0] == gate->bit_idx)
			return ctrl->gates[n];
	}
	return ERR_PTR(-ENODEV);
}