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
struct img_i2c {int /*<<< orphan*/  sys_clk; int /*<<< orphan*/  scb_clk; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct img_i2c* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int img_i2c_runtime_resume(struct device *dev)
{
	struct img_i2c *i2c = dev_get_drvdata(dev);
	int ret;

	ret = clk_prepare_enable(i2c->sys_clk);
	if (ret) {
		dev_err(dev, "Unable to enable sys clock\n");
		return ret;
	}

	ret = clk_prepare_enable(i2c->scb_clk);
	if (ret) {
		dev_err(dev, "Unable to enable scb clock\n");
		clk_disable_unprepare(i2c->sys_clk);
		return ret;
	}

	return 0;
}