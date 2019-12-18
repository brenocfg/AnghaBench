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
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct dwc3_exynos_driverdata {int num_clks; size_t suspend_clk_idx; scalar_t__ clk_names; } ;
struct dwc3_exynos {int num_clks; char const** clk_names; size_t suspend_clk_idx; void** clks; void* vdd33; void* vdd10; struct device* dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 void* devm_clk_get (struct device*,char const*) ; 
 struct dwc3_exynos* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* devm_regulator_get (struct device*,char*) ; 
 struct dwc3_exynos_driverdata* of_device_get_match_data (struct device*) ; 
 int of_platform_populate (struct device_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct dwc3_exynos*) ; 
 int /*<<< orphan*/  regulator_disable (void*) ; 
 int regulator_enable (void*) ; 

__attribute__((used)) static int dwc3_exynos_probe(struct platform_device *pdev)
{
	struct dwc3_exynos	*exynos;
	struct device		*dev = &pdev->dev;
	struct device_node	*node = dev->of_node;
	const struct dwc3_exynos_driverdata *driver_data;
	int			i, ret;

	exynos = devm_kzalloc(dev, sizeof(*exynos), GFP_KERNEL);
	if (!exynos)
		return -ENOMEM;

	driver_data = of_device_get_match_data(dev);
	exynos->dev = dev;
	exynos->num_clks = driver_data->num_clks;
	exynos->clk_names = (const char **)driver_data->clk_names;
	exynos->suspend_clk_idx = driver_data->suspend_clk_idx;

	platform_set_drvdata(pdev, exynos);

	for (i = 0; i < exynos->num_clks; i++) {
		exynos->clks[i] = devm_clk_get(dev, exynos->clk_names[i]);
		if (IS_ERR(exynos->clks[i])) {
			dev_err(dev, "failed to get clock: %s\n",
				exynos->clk_names[i]);
			return PTR_ERR(exynos->clks[i]);
		}
	}

	for (i = 0; i < exynos->num_clks; i++) {
		ret = clk_prepare_enable(exynos->clks[i]);
		if (ret) {
			while (i-- > 0)
				clk_disable_unprepare(exynos->clks[i]);
			return ret;
		}
	}

	if (exynos->suspend_clk_idx >= 0)
		clk_prepare_enable(exynos->clks[exynos->suspend_clk_idx]);

	exynos->vdd33 = devm_regulator_get(dev, "vdd33");
	if (IS_ERR(exynos->vdd33)) {
		ret = PTR_ERR(exynos->vdd33);
		goto vdd33_err;
	}
	ret = regulator_enable(exynos->vdd33);
	if (ret) {
		dev_err(dev, "Failed to enable VDD33 supply\n");
		goto vdd33_err;
	}

	exynos->vdd10 = devm_regulator_get(dev, "vdd10");
	if (IS_ERR(exynos->vdd10)) {
		ret = PTR_ERR(exynos->vdd10);
		goto vdd10_err;
	}
	ret = regulator_enable(exynos->vdd10);
	if (ret) {
		dev_err(dev, "Failed to enable VDD10 supply\n");
		goto vdd10_err;
	}

	if (node) {
		ret = of_platform_populate(node, NULL, NULL, dev);
		if (ret) {
			dev_err(dev, "failed to add dwc3 core\n");
			goto populate_err;
		}
	} else {
		dev_err(dev, "no device node, failed to add dwc3 core\n");
		ret = -ENODEV;
		goto populate_err;
	}

	return 0;

populate_err:
	regulator_disable(exynos->vdd10);
vdd10_err:
	regulator_disable(exynos->vdd33);
vdd33_err:
	for (i = exynos->num_clks - 1; i >= 0; i--)
		clk_disable_unprepare(exynos->clks[i]);

	if (exynos->suspend_clk_idx >= 0)
		clk_disable_unprepare(exynos->clks[exynos->suspend_clk_idx]);

	return ret;
}