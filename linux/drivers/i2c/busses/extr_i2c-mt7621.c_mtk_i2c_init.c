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
struct mtk_i2c {int clk_div; int bus_freq; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int SM0CTL0_CLK_DIV_MAX ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_i2c_reset (struct mtk_i2c*) ; 

__attribute__((used)) static void mtk_i2c_init(struct mtk_i2c *i2c)
{
	i2c->clk_div = clk_get_rate(i2c->clk) / i2c->bus_freq - 1;
	if (i2c->clk_div < 99)
		i2c->clk_div = 99;
	if (i2c->clk_div > SM0CTL0_CLK_DIV_MAX)
		i2c->clk_div = SM0CTL0_CLK_DIV_MAX;

	mtk_i2c_reset(i2c);
}