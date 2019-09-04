#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vc5_driver_data {TYPE_2__* clk_out; TYPE_1__* chip_info; } ;
struct of_phandle_args {unsigned int* args; } ;
struct clk_hw {int dummy; } ;
struct TYPE_4__ {struct clk_hw hw; } ;
struct TYPE_3__ {unsigned int clk_out_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct clk_hw* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct clk_hw *vc5_of_clk_get(struct of_phandle_args *clkspec,
				     void *data)
{
	struct vc5_driver_data *vc5 = data;
	unsigned int idx = clkspec->args[0];

	if (idx >= vc5->chip_info->clk_out_cnt)
		return ERR_PTR(-EINVAL);

	return &vc5->clk_out[idx].hw;
}