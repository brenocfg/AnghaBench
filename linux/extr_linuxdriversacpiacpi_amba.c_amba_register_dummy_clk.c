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
 int /*<<< orphan*/  clk_register_clkdev (struct clk*,char*,int /*<<< orphan*/ *) ; 
 struct clk* clk_register_fixed_rate (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void amba_register_dummy_clk(void)
{
	static struct clk *amba_dummy_clk;

	/* If clock already registered */
	if (amba_dummy_clk)
		return;

	amba_dummy_clk = clk_register_fixed_rate(NULL, "apb_pclk", NULL, 0, 0);
	clk_register_clkdev(amba_dummy_clk, "apb_pclk", NULL);
}