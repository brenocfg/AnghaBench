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
struct clk_bulk_data {int /*<<< orphan*/ * clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ *) ; 

void clk_bulk_put(int num_clks, struct clk_bulk_data *clks)
{
	while (--num_clks >= 0) {
		clk_put(clks[num_clks].clk);
		clks[num_clks].clk = NULL;
	}
}