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
struct sun4i_frontend {int /*<<< orphan*/  regs; int /*<<< orphan*/  reset; int /*<<< orphan*/  ram_clk; int /*<<< orphan*/  mod_clk; int /*<<< orphan*/  bus_clk; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUN4I_FRONTEND_EN_EN ; 
 int /*<<< orphan*/  SUN4I_FRONTEND_EN_REG ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct sun4i_frontend* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int reset_control_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun4i_frontend_scaler_init (struct sun4i_frontend*) ; 

__attribute__((used)) static int sun4i_frontend_runtime_resume(struct device *dev)
{
	struct sun4i_frontend *frontend = dev_get_drvdata(dev);
	int ret;

	clk_set_rate(frontend->mod_clk, 300000000);

	clk_prepare_enable(frontend->bus_clk);
	clk_prepare_enable(frontend->mod_clk);
	clk_prepare_enable(frontend->ram_clk);

	ret = reset_control_reset(frontend->reset);
	if (ret) {
		dev_err(dev, "Couldn't reset our device\n");
		return ret;
	}

	regmap_update_bits(frontend->regs, SUN4I_FRONTEND_EN_REG,
			   SUN4I_FRONTEND_EN_EN,
			   SUN4I_FRONTEND_EN_EN);

	sun4i_frontend_scaler_init(frontend);

	return 0;
}