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
typedef  int u16 ;
struct clk_syscon {scalar_t__ clk_val; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ U300_SYSCON_CCR ; 
 int U300_SYSCON_CCR_CLKING_PERFORMANCE_BEST ; 
 int U300_SYSCON_CCR_CLKING_PERFORMANCE_HIGH ; 
 int U300_SYSCON_CCR_CLKING_PERFORMANCE_INTERMEDIATE ; 
 int U300_SYSCON_CCR_CLKING_PERFORMANCE_LOW_POWER ; 
 int U300_SYSCON_CCR_CLKING_PERFORMANCE_MASK ; 
 scalar_t__ U300_SYSCON_SBCER_CPU_CLK_EN ; 
 int readw (scalar_t__) ; 
 scalar_t__ syscon_vbase ; 
 struct clk_syscon* to_syscon (struct clk_hw*) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int syscon_clk_set_rate(struct clk_hw *hw, unsigned long rate,
			       unsigned long parent_rate)
{
	struct clk_syscon *sclk = to_syscon(hw);
	u16 val;

	/* We only support setting the rate of the CPU clock */
	if (sclk->clk_val != U300_SYSCON_SBCER_CPU_CLK_EN)
		return -EINVAL;
	switch (rate) {
	case 13000000:
		val = U300_SYSCON_CCR_CLKING_PERFORMANCE_LOW_POWER;
		break;
	case 52000000:
		val = U300_SYSCON_CCR_CLKING_PERFORMANCE_INTERMEDIATE;
		break;
	case 104000000:
		val = U300_SYSCON_CCR_CLKING_PERFORMANCE_HIGH;
		break;
	case 208000000:
		val = U300_SYSCON_CCR_CLKING_PERFORMANCE_BEST;
		break;
	default:
		return -EINVAL;
	}
	val |= readw(syscon_vbase + U300_SYSCON_CCR) &
		~U300_SYSCON_CCR_CLKING_PERFORMANCE_MASK ;
	writew(val, syscon_vbase + U300_SYSCON_CCR);
	return 0;
}