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
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct clk* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 struct clk* clk_get (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 

__attribute__((used)) static struct clk *spear1340_cpu_get_possible_parent(unsigned long newfreq)
{
	struct clk *sys_pclk;
	int pclk;
	/*
	 * In SPEAr1340, cpu clk's parent sys clk can take input from
	 * following sources
	 */
	const char *sys_clk_src[] = {
		"sys_syn_clk",
		"pll1_clk",
		"pll2_clk",
		"pll3_clk",
	};

	/*
	 * As sys clk can have multiple source with their own range
	 * limitation so we choose possible sources accordingly
	 */
	if (newfreq <= 300000000)
		pclk = 0; /* src is sys_syn_clk */
	else if (newfreq > 300000000 && newfreq <= 500000000)
		pclk = 3; /* src is pll3_clk */
	else if (newfreq == 600000000)
		pclk = 1; /* src is pll1_clk */
	else
		return ERR_PTR(-EINVAL);

	/* Get parent to sys clock */
	sys_pclk = clk_get(NULL, sys_clk_src[pclk]);
	if (IS_ERR(sys_pclk))
		pr_err("Failed to get %s clock\n", sys_clk_src[pclk]);

	return sys_pclk;
}