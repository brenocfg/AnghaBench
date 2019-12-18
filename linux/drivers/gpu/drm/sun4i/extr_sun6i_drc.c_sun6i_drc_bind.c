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
struct sun6i_drc {void* reset; void* bus_clk; void* mod_clk; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int /*<<< orphan*/  clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct sun6i_drc*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 struct sun6i_drc* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* devm_reset_control_get (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_control_assert (void*) ; 
 int reset_control_deassert (void*) ; 

__attribute__((used)) static int sun6i_drc_bind(struct device *dev, struct device *master,
			 void *data)
{
	struct sun6i_drc *drc;
	int ret;

	drc = devm_kzalloc(dev, sizeof(*drc), GFP_KERNEL);
	if (!drc)
		return -ENOMEM;
	dev_set_drvdata(dev, drc);

	drc->reset = devm_reset_control_get(dev, NULL);
	if (IS_ERR(drc->reset)) {
		dev_err(dev, "Couldn't get our reset line\n");
		return PTR_ERR(drc->reset);
	}

	ret = reset_control_deassert(drc->reset);
	if (ret) {
		dev_err(dev, "Couldn't deassert our reset line\n");
		return ret;
	}

	drc->bus_clk = devm_clk_get(dev, "ahb");
	if (IS_ERR(drc->bus_clk)) {
		dev_err(dev, "Couldn't get our bus clock\n");
		ret = PTR_ERR(drc->bus_clk);
		goto err_assert_reset;
	}
	clk_prepare_enable(drc->bus_clk);

	drc->mod_clk = devm_clk_get(dev, "mod");
	if (IS_ERR(drc->mod_clk)) {
		dev_err(dev, "Couldn't get our mod clock\n");
		ret = PTR_ERR(drc->mod_clk);
		goto err_disable_bus_clk;
	}
	clk_prepare_enable(drc->mod_clk);

	return 0;

err_disable_bus_clk:
	clk_disable_unprepare(drc->bus_clk);
err_assert_reset:
	reset_control_assert(drc->reset);
	return ret;
}