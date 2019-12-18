#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* funcs; } ;
struct TYPE_8__ {TYPE_1__* funcs; } ;
struct rk3066_hdmi {int /*<<< orphan*/ * hclk; int /*<<< orphan*/ * ddc; TYPE_3__ encoder; TYPE_4__ connector; int /*<<< orphan*/ * grf_regmap; int /*<<< orphan*/ * regs; struct drm_device* drm_dev; struct device* dev; } ;
struct resource {int dummy; } ;
struct platform_device {int dummy; } ;
struct drm_device {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* destroy ) (TYPE_3__*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* destroy ) (TYPE_4__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,...) ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HDMI_INTERNAL_CLK_DIVIDER ; 
 int HDMI_INTR_HOTPLUG ; 
 int /*<<< orphan*/  HDMI_INTR_MASK1 ; 
 int /*<<< orphan*/  HDMI_INTR_MASK2 ; 
 int /*<<< orphan*/  HDMI_INTR_MASK3 ; 
 int /*<<< orphan*/  HDMI_INTR_MASK4 ; 
 int /*<<< orphan*/  HDMI_SYS_POWER_MODE_A ; 
 int /*<<< orphan*/  HDMI_SYS_POWER_MODE_B ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ *) ; 
 int clk_prepare_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct rk3066_hdmi*) ; 
 int /*<<< orphan*/ * devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/ * devm_ioremap_resource (struct device*,struct resource*) ; 
 struct rk3066_hdmi* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rk3066_hdmi*) ; 
 int /*<<< orphan*/  hdmi_writeb (struct rk3066_hdmi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_put_adapter (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk3066_hdmi_hardirq ; 
 int /*<<< orphan*/ * rk3066_hdmi_i2c_adapter (struct rk3066_hdmi*) ; 
 int /*<<< orphan*/  rk3066_hdmi_irq ; 
 int rk3066_hdmi_register (struct drm_device*,struct rk3066_hdmi*) ; 
 int /*<<< orphan*/  rk3066_hdmi_set_power_mode (struct rk3066_hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 
 int /*<<< orphan*/ * syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 
 struct platform_device* to_platform_device (struct device*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int rk3066_hdmi_bind(struct device *dev, struct device *master,
			    void *data)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct drm_device *drm = data;
	struct rk3066_hdmi *hdmi;
	struct resource *iores;
	int irq;
	int ret;

	hdmi = devm_kzalloc(dev, sizeof(*hdmi), GFP_KERNEL);
	if (!hdmi)
		return -ENOMEM;

	hdmi->dev = dev;
	hdmi->drm_dev = drm;

	iores = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!iores)
		return -ENXIO;

	hdmi->regs = devm_ioremap_resource(dev, iores);
	if (IS_ERR(hdmi->regs))
		return PTR_ERR(hdmi->regs);

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	hdmi->hclk = devm_clk_get(dev, "hclk");
	if (IS_ERR(hdmi->hclk)) {
		DRM_DEV_ERROR(dev, "unable to get HDMI hclk clock\n");
		return PTR_ERR(hdmi->hclk);
	}

	ret = clk_prepare_enable(hdmi->hclk);
	if (ret) {
		DRM_DEV_ERROR(dev, "cannot enable HDMI hclk clock: %d\n", ret);
		return ret;
	}

	hdmi->grf_regmap = syscon_regmap_lookup_by_phandle(dev->of_node,
							   "rockchip,grf");
	if (IS_ERR(hdmi->grf_regmap)) {
		DRM_DEV_ERROR(dev, "unable to get rockchip,grf\n");
		ret = PTR_ERR(hdmi->grf_regmap);
		goto err_disable_hclk;
	}

	/* internal hclk = hdmi_hclk / 25 */
	hdmi_writeb(hdmi, HDMI_INTERNAL_CLK_DIVIDER, 25);

	hdmi->ddc = rk3066_hdmi_i2c_adapter(hdmi);
	if (IS_ERR(hdmi->ddc)) {
		ret = PTR_ERR(hdmi->ddc);
		hdmi->ddc = NULL;
		goto err_disable_hclk;
	}

	rk3066_hdmi_set_power_mode(hdmi, HDMI_SYS_POWER_MODE_B);
	usleep_range(999, 1000);
	hdmi_writeb(hdmi, HDMI_INTR_MASK1, HDMI_INTR_HOTPLUG);
	hdmi_writeb(hdmi, HDMI_INTR_MASK2, 0);
	hdmi_writeb(hdmi, HDMI_INTR_MASK3, 0);
	hdmi_writeb(hdmi, HDMI_INTR_MASK4, 0);
	rk3066_hdmi_set_power_mode(hdmi, HDMI_SYS_POWER_MODE_A);

	ret = rk3066_hdmi_register(drm, hdmi);
	if (ret)
		goto err_disable_i2c;

	dev_set_drvdata(dev, hdmi);

	ret = devm_request_threaded_irq(dev, irq, rk3066_hdmi_hardirq,
					rk3066_hdmi_irq, IRQF_SHARED,
					dev_name(dev), hdmi);
	if (ret) {
		DRM_DEV_ERROR(dev, "failed to request hdmi irq: %d\n", ret);
		goto err_cleanup_hdmi;
	}

	return 0;

err_cleanup_hdmi:
	hdmi->connector.funcs->destroy(&hdmi->connector);
	hdmi->encoder.funcs->destroy(&hdmi->encoder);
err_disable_i2c:
	i2c_put_adapter(hdmi->ddc);
err_disable_hclk:
	clk_disable_unprepare(hdmi->hclk);

	return ret;
}