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
struct icst_vco {int dummy; } ;
struct clk_icst {unsigned long rate; TYPE_1__* params; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {unsigned long ref; } ;

/* Variables and functions */
 unsigned long icst_hz (TYPE_1__*,struct icst_vco) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct clk_icst* to_icst (struct clk_hw*) ; 
 int vco_get (struct clk_icst*,struct icst_vco*) ; 

__attribute__((used)) static unsigned long icst_recalc_rate(struct clk_hw *hw,
				      unsigned long parent_rate)
{
	struct clk_icst *icst = to_icst(hw);
	struct icst_vco vco;
	int ret;

	if (parent_rate)
		icst->params->ref = parent_rate;
	ret = vco_get(icst, &vco);
	if (ret) {
		pr_err("ICST: could not get VCO setting\n");
		return 0;
	}
	icst->rate = icst_hz(icst->params, vco);
	return icst->rate;
}