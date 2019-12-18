#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/ * funcs; } ;
struct exynos_mic {TYPE_1__ bridge; int /*<<< orphan*/ * clks; int /*<<< orphan*/  sysreg; int /*<<< orphan*/  reg; struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (struct device*,char*) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,...) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int NUM_CLKS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * clk_names ; 
 int component_add (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct exynos_mic* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_bridge_add (TYPE_1__*) ; 
 int /*<<< orphan*/  exynos_mic_component_ops ; 
 int /*<<< orphan*/  mic_bridge_funcs ; 
 int of_address_to_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct exynos_mic*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int exynos_mic_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct exynos_mic *mic;
	struct resource res;
	int ret, i;

	mic = devm_kzalloc(dev, sizeof(*mic), GFP_KERNEL);
	if (!mic) {
		DRM_DEV_ERROR(dev,
			      "mic: Failed to allocate memory for MIC object\n");
		ret = -ENOMEM;
		goto err;
	}

	mic->dev = dev;

	ret = of_address_to_resource(dev->of_node, 0, &res);
	if (ret) {
		DRM_DEV_ERROR(dev, "mic: Failed to get mem region for MIC\n");
		goto err;
	}
	mic->reg = devm_ioremap(dev, res.start, resource_size(&res));
	if (!mic->reg) {
		DRM_DEV_ERROR(dev, "mic: Failed to remap for MIC\n");
		ret = -ENOMEM;
		goto err;
	}

	mic->sysreg = syscon_regmap_lookup_by_phandle(dev->of_node,
							"samsung,disp-syscon");
	if (IS_ERR(mic->sysreg)) {
		DRM_DEV_ERROR(dev, "mic: Failed to get system register.\n");
		ret = PTR_ERR(mic->sysreg);
		goto err;
	}

	for (i = 0; i < NUM_CLKS; i++) {
		mic->clks[i] = devm_clk_get(dev, clk_names[i]);
		if (IS_ERR(mic->clks[i])) {
			DRM_DEV_ERROR(dev, "mic: Failed to get clock (%s)\n",
				      clk_names[i]);
			ret = PTR_ERR(mic->clks[i]);
			goto err;
		}
	}

	platform_set_drvdata(pdev, mic);

	mic->bridge.funcs = &mic_bridge_funcs;
	mic->bridge.of_node = dev->of_node;

	drm_bridge_add(&mic->bridge);

	pm_runtime_enable(dev);

	ret = component_add(dev, &exynos_mic_component_ops);
	if (ret)
		goto err_pm;

	DRM_DEV_DEBUG_KMS(dev, "MIC has been probed\n");

	return 0;

err_pm:
	pm_runtime_disable(dev);
err:
	return ret;
}