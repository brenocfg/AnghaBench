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
struct clk_plt {int /*<<< orphan*/  lookup; } ;

/* Variables and functions */
 int /*<<< orphan*/  clkdev_drop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void plt_clk_unregister(struct clk_plt *pclk)
{
	clkdev_drop(pclk->lookup);
}