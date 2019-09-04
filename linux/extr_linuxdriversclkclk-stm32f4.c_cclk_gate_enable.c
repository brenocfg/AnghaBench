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
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int (* enable ) (struct clk_hw*) ;} ;

/* Variables and functions */
 TYPE_1__ clk_gate_ops ; 
 int /*<<< orphan*/  disable_power_domain_write_protection () ; 
 int /*<<< orphan*/  enable_power_domain_write_protection () ; 
 int stub1 (struct clk_hw*) ; 

__attribute__((used)) static int cclk_gate_enable(struct clk_hw *hw)
{
	int ret;

	disable_power_domain_write_protection();

	ret = clk_gate_ops.enable(hw);

	enable_power_domain_write_protection();

	return ret;
}