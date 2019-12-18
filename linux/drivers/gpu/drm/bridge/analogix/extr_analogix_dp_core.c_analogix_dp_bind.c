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
struct resource {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct drm_device {int dummy; } ;
struct analogix_dp_plat_data {int /*<<< orphan*/  encoder; } ;
struct TYPE_2__ {char* name; struct device* dev; int /*<<< orphan*/  transfer; } ;
struct analogix_dp_device {int panel_is_modeset; TYPE_1__ aux; struct analogix_dp_plat_data* plat_data; int /*<<< orphan*/  encoder; struct drm_device* drm_dev; int /*<<< orphan*/  irq; int /*<<< orphan*/ * hpd_gpiod; int /*<<< orphan*/  force_hpd; int /*<<< orphan*/ * reg_base; int /*<<< orphan*/ * clock; int /*<<< orphan*/ * phy; struct device* dev; int /*<<< orphan*/  panel_lock; int /*<<< orphan*/  dpms_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  DRM_MODE_DPMS_OFF ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  ENXIO ; 
 struct analogix_dp_device* ERR_CAST (int /*<<< orphan*/ *) ; 
 struct analogix_dp_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 unsigned int IRQF_TRIGGER_FALLING ; 
 unsigned int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int analogix_dp_create_bridge (struct drm_device*,struct analogix_dp_device*) ; 
 int analogix_dp_dt_parse_pdata (struct analogix_dp_device*) ; 
 int /*<<< orphan*/  analogix_dp_hardirq ; 
 int /*<<< orphan*/  analogix_dp_irq_thread ; 
 int /*<<< orphan*/  analogix_dpaux_transfer ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/ * devm_clk_get (struct device*,char*) ; 
 void* devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_ioremap_resource (struct device*,struct resource*) ; 
 struct analogix_dp_device* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_phy_get (struct device*,char*) ; 
 int devm_request_threaded_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,char*,struct analogix_dp_device*) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int drm_dp_aux_register (TYPE_1__*) ; 
 int /*<<< orphan*/  gpiod_to_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

struct analogix_dp_device *
analogix_dp_bind(struct device *dev, struct drm_device *drm_dev,
		 struct analogix_dp_plat_data *plat_data)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct analogix_dp_device *dp;
	struct resource *res;
	unsigned int irq_flags;
	int ret;

	if (!plat_data) {
		dev_err(dev, "Invalided input plat_data\n");
		return ERR_PTR(-EINVAL);
	}

	dp = devm_kzalloc(dev, sizeof(struct analogix_dp_device), GFP_KERNEL);
	if (!dp)
		return ERR_PTR(-ENOMEM);

	dp->dev = &pdev->dev;
	dp->dpms_mode = DRM_MODE_DPMS_OFF;

	mutex_init(&dp->panel_lock);
	dp->panel_is_modeset = false;

	/*
	 * platform dp driver need containor_of the plat_data to get
	 * the driver private data, so we need to store the point of
	 * plat_data, not the context of plat_data.
	 */
	dp->plat_data = plat_data;

	ret = analogix_dp_dt_parse_pdata(dp);
	if (ret)
		return ERR_PTR(ret);

	dp->phy = devm_phy_get(dp->dev, "dp");
	if (IS_ERR(dp->phy)) {
		dev_err(dp->dev, "no DP phy configured\n");
		ret = PTR_ERR(dp->phy);
		if (ret) {
			/*
			 * phy itself is not enabled, so we can move forward
			 * assigning NULL to phy pointer.
			 */
			if (ret == -ENOSYS || ret == -ENODEV)
				dp->phy = NULL;
			else
				return ERR_PTR(ret);
		}
	}

	dp->clock = devm_clk_get(&pdev->dev, "dp");
	if (IS_ERR(dp->clock)) {
		dev_err(&pdev->dev, "failed to get clock\n");
		return ERR_CAST(dp->clock);
	}

	clk_prepare_enable(dp->clock);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	dp->reg_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(dp->reg_base))
		return ERR_CAST(dp->reg_base);

	dp->force_hpd = of_property_read_bool(dev->of_node, "force-hpd");

	/* Try two different names */
	dp->hpd_gpiod = devm_gpiod_get_optional(dev, "hpd", GPIOD_IN);
	if (!dp->hpd_gpiod)
		dp->hpd_gpiod = devm_gpiod_get_optional(dev, "samsung,hpd",
							GPIOD_IN);
	if (IS_ERR(dp->hpd_gpiod)) {
		dev_err(dev, "error getting HDP GPIO: %ld\n",
			PTR_ERR(dp->hpd_gpiod));
		return ERR_CAST(dp->hpd_gpiod);
	}

	if (dp->hpd_gpiod) {
		/*
		 * Set up the hotplug GPIO from the device tree as an interrupt.
		 * Simply specifying a different interrupt in the device tree
		 * doesn't work since we handle hotplug rather differently when
		 * using a GPIO.  We also need the actual GPIO specifier so
		 * that we can get the current state of the GPIO.
		 */
		dp->irq = gpiod_to_irq(dp->hpd_gpiod);
		irq_flags = IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING;
	} else {
		dp->irq = platform_get_irq(pdev, 0);
		irq_flags = 0;
	}

	if (dp->irq == -ENXIO) {
		dev_err(&pdev->dev, "failed to get irq\n");
		return ERR_PTR(-ENODEV);
	}

	ret = devm_request_threaded_irq(&pdev->dev, dp->irq,
					analogix_dp_hardirq,
					analogix_dp_irq_thread,
					irq_flags, "analogix-dp", dp);
	if (ret) {
		dev_err(&pdev->dev, "failed to request irq\n");
		goto err_disable_pm_runtime;
	}
	disable_irq(dp->irq);

	dp->drm_dev = drm_dev;
	dp->encoder = dp->plat_data->encoder;

	dp->aux.name = "DP-AUX";
	dp->aux.transfer = analogix_dpaux_transfer;
	dp->aux.dev = &pdev->dev;

	ret = drm_dp_aux_register(&dp->aux);
	if (ret)
		return ERR_PTR(ret);

	pm_runtime_enable(dev);

	ret = analogix_dp_create_bridge(drm_dev, dp);
	if (ret) {
		DRM_ERROR("failed to create bridge (%d)\n", ret);
		goto err_disable_pm_runtime;
	}

	return dp;

err_disable_pm_runtime:

	pm_runtime_disable(dev);

	return ERR_PTR(ret);
}