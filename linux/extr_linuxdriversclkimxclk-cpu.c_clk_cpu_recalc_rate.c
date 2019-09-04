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
struct clk_hw {int dummy; } ;
struct clk_cpu {int /*<<< orphan*/  div; } ;

/* Variables and functions */
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 struct clk_cpu* to_clk_cpu (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_cpu_recalc_rate(struct clk_hw *hw,
					 unsigned long parent_rate)
{
	struct clk_cpu *cpu = to_clk_cpu(hw);

	return clk_get_rate(cpu->div);
}