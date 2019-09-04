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
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 unsigned int KHz ; 
 struct clk* clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (struct clk*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 int /*<<< orphan*/ * get_freq_khz ; 
 int /*<<< orphan*/  pr_info (char*,unsigned long,unsigned long) ; 

unsigned int pxa25x_get_clk_frequency_khz(int info)
{
	struct clk *clk;
	unsigned long clks[5];
	int i;

	for (i = 0; i < ARRAY_SIZE(get_freq_khz); i++) {
		clk = clk_get(NULL, get_freq_khz[i]);
		if (IS_ERR(clk)) {
			clks[i] = 0;
		} else {
			clks[i] = clk_get_rate(clk);
			clk_put(clk);
		}
	}

	if (info) {
		pr_info("Run Mode clock: %ld.%02ldMHz\n",
			clks[1] / 1000000, (clks[1] % 1000000) / 10000);
		pr_info("Turbo Mode clock: %ld.%02ldMHz\n",
			clks[2] / 1000000, (clks[2] % 1000000) / 10000);
		pr_info("Memory clock: %ld.%02ldMHz\n",
			clks[3] / 1000000, (clks[3] % 1000000) / 10000);
	}

	return (unsigned int)clks[0] / KHz;
}