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
struct mtk_eth {int /*<<< orphan*/ * clks; } ;

/* Variables and functions */
 int MTK_CLK_MAX ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_clk_disable(struct mtk_eth *eth)
{
	int clk;

	for (clk = MTK_CLK_MAX - 1; clk >= 0; clk--)
		clk_disable_unprepare(eth->clks[clk]);
}