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
struct sun4i_backend {int /*<<< orphan*/  sat_reset; int /*<<< orphan*/  sat_clk; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct sun4i_backend* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  devm_reset_control_get (struct device*,char*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun4i_backend_init_sat(struct device *dev) {
	struct sun4i_backend *backend = dev_get_drvdata(dev);
	int ret;

	backend->sat_reset = devm_reset_control_get(dev, "sat");
	if (IS_ERR(backend->sat_reset)) {
		dev_err(dev, "Couldn't get the SAT reset line\n");
		return PTR_ERR(backend->sat_reset);
	}

	ret = reset_control_deassert(backend->sat_reset);
	if (ret) {
		dev_err(dev, "Couldn't deassert the SAT reset line\n");
		return ret;
	}

	backend->sat_clk = devm_clk_get(dev, "sat");
	if (IS_ERR(backend->sat_clk)) {
		dev_err(dev, "Couldn't get our SAT clock\n");
		ret = PTR_ERR(backend->sat_clk);
		goto err_assert_reset;
	}

	ret = clk_prepare_enable(backend->sat_clk);
	if (ret) {
		dev_err(dev, "Couldn't enable the SAT clock\n");
		return ret;
	}

	return 0;

err_assert_reset:
	reset_control_assert(backend->sat_reset);
	return ret;
}