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
struct mtk_i2c {scalar_t__ clk_dma; scalar_t__ clk_main; scalar_t__ clk_pmic; scalar_t__ have_pmic; scalar_t__ clk_arb; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 

__attribute__((used)) static void mtk_i2c_clock_disable(struct mtk_i2c *i2c)
{
	if (i2c->clk_arb)
		clk_disable_unprepare(i2c->clk_arb);

	if (i2c->have_pmic)
		clk_disable_unprepare(i2c->clk_pmic);

	clk_disable_unprepare(i2c->clk_main);
	clk_disable_unprepare(i2c->clk_dma);
}