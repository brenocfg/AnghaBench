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
struct i2c_msg {int dummy; } ;
struct i2c_adapter {struct exynos5_i2c* algo_data; } ;
struct exynos5_i2c {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int exynos5_i2c_xfer_msg (struct exynos5_i2c*,struct i2c_msg*,int) ; 

__attribute__((used)) static int exynos5_i2c_xfer(struct i2c_adapter *adap,
			struct i2c_msg *msgs, int num)
{
	struct exynos5_i2c *i2c = adap->algo_data;
	int i, ret;

	ret = clk_enable(i2c->clk);
	if (ret)
		return ret;

	for (i = 0; i < num; ++i) {
		ret = exynos5_i2c_xfer_msg(i2c, msgs + i, i + 1 == num);
		if (ret)
			break;
	}

	clk_disable(i2c->clk);

	return ret ?: num;
}