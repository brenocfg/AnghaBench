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
struct lima_device {int /*<<< orphan*/ * clk_bus; int /*<<< orphan*/ * clk_gpu; int /*<<< orphan*/  dev; int /*<<< orphan*/ * reset; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ *) ; 
 int clk_prepare_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 void* devm_clk_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * devm_reset_control_get_optional (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int reset_control_deassert (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lima_clk_init(struct lima_device *dev)
{
	int err;

	dev->clk_bus = devm_clk_get(dev->dev, "bus");
	if (IS_ERR(dev->clk_bus)) {
		err = PTR_ERR(dev->clk_bus);
		if (err != -EPROBE_DEFER)
			dev_err(dev->dev, "get bus clk failed %d\n", err);
		return err;
	}

	dev->clk_gpu = devm_clk_get(dev->dev, "core");
	if (IS_ERR(dev->clk_gpu)) {
		err = PTR_ERR(dev->clk_gpu);
		if (err != -EPROBE_DEFER)
			dev_err(dev->dev, "get core clk failed %d\n", err);
		return err;
	}

	err = clk_prepare_enable(dev->clk_bus);
	if (err)
		return err;

	err = clk_prepare_enable(dev->clk_gpu);
	if (err)
		goto error_out0;

	dev->reset = devm_reset_control_get_optional(dev->dev, NULL);
	if (IS_ERR(dev->reset)) {
		err = PTR_ERR(dev->reset);
		if (err != -EPROBE_DEFER)
			dev_err(dev->dev, "get reset controller failed %d\n",
				err);
		goto error_out1;
	} else if (dev->reset != NULL) {
		err = reset_control_deassert(dev->reset);
		if (err) {
			dev_err(dev->dev,
				"reset controller deassert failed %d\n", err);
			goto error_out1;
		}
	}

	return 0;

error_out1:
	clk_disable_unprepare(dev->clk_gpu);
error_out0:
	clk_disable_unprepare(dev->clk_bus);
	return err;
}