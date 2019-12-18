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
struct dss_clk {int /*<<< orphan*/ * clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ *) ; 

void msm_dss_put_clk(struct dss_clk *clk_arry, int num_clk)
{
	int i;

	for (i = num_clk - 1; i >= 0; i--) {
		if (clk_arry[i].clk)
			clk_put(clk_arry[i].clk);
		clk_arry[i].clk = NULL;
	}
}