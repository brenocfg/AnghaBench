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
struct mtk_i2c {int /*<<< orphan*/  clk_dma; int /*<<< orphan*/  clk_main; int /*<<< orphan*/  clk_pmic; scalar_t__ have_pmic; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_i2c_clock_enable(struct mtk_i2c *i2c)
{
	int ret;

	ret = clk_prepare_enable(i2c->clk_dma);
	if (ret)
		return ret;

	ret = clk_prepare_enable(i2c->clk_main);
	if (ret)
		goto err_main;

	if (i2c->have_pmic) {
		ret = clk_prepare_enable(i2c->clk_pmic);
		if (ret)
			goto err_pmic;
	}
	return 0;

err_pmic:
	clk_disable_unprepare(i2c->clk_main);
err_main:
	clk_disable_unprepare(i2c->clk_dma);

	return ret;
}