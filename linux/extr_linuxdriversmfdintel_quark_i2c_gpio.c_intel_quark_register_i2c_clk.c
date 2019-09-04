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
struct intel_quark_mfd {struct clk* i2c_clk; int /*<<< orphan*/  i2c_clk_lookup; } ;
struct device {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INTEL_QUARK_I2C_CLK_HZ ; 
 int /*<<< orphan*/  INTEL_QUARK_I2C_CONTROLLER_CLK ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 struct clk* clk_register_fixed_rate (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unregister (struct clk*) ; 
 int /*<<< orphan*/  clkdev_create (struct clk*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct intel_quark_mfd* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int intel_quark_register_i2c_clk(struct device *dev)
{
	struct intel_quark_mfd *quark_mfd = dev_get_drvdata(dev);
	struct clk *i2c_clk;

	i2c_clk = clk_register_fixed_rate(dev,
					  INTEL_QUARK_I2C_CONTROLLER_CLK, NULL,
					  0, INTEL_QUARK_I2C_CLK_HZ);
	if (IS_ERR(i2c_clk))
		return PTR_ERR(i2c_clk);

	quark_mfd->i2c_clk = i2c_clk;
	quark_mfd->i2c_clk_lookup = clkdev_create(i2c_clk, NULL,
						INTEL_QUARK_I2C_CONTROLLER_CLK);

	if (!quark_mfd->i2c_clk_lookup) {
		clk_unregister(quark_mfd->i2c_clk);
		dev_err(dev, "Fixed clk register failed\n");
		return -ENOMEM;
	}

	return 0;
}