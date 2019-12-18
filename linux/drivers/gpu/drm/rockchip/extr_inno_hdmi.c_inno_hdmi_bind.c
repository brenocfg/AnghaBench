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
struct resource {int dummy; } ;
struct platform_device {int dummy; } ;
struct TYPE_7__ {TYPE_2__* funcs; } ;
struct TYPE_8__ {TYPE_1__* funcs; } ;
struct inno_hdmi {int /*<<< orphan*/ * pclk; int /*<<< orphan*/ * ddc; TYPE_3__ encoder; TYPE_4__ connector; int /*<<< orphan*/  tmds_rate; struct device* dev; int /*<<< orphan*/ * regs; struct drm_device* drm_dev; } ;
struct drm_device {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* destroy ) (TYPE_3__*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* destroy ) (TYPE_4__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,...) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HDMI_STATUS ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ *) ; 
 int clk_prepare_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct inno_hdmi*) ; 
 int /*<<< orphan*/ * devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/ * devm_ioremap_resource (struct device*,struct resource*) ; 
 struct inno_hdmi* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct inno_hdmi*) ; 
 int /*<<< orphan*/  hdmi_modb (struct inno_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_put_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inno_hdmi_hardirq ; 
 int /*<<< orphan*/ * inno_hdmi_i2c_adapter (struct inno_hdmi*) ; 
 int /*<<< orphan*/  inno_hdmi_i2c_init (struct inno_hdmi*) ; 
 int /*<<< orphan*/  inno_hdmi_irq ; 
 int inno_hdmi_register (struct drm_device*,struct inno_hdmi*) ; 
 int /*<<< orphan*/  inno_hdmi_reset (struct inno_hdmi*) ; 
 int /*<<< orphan*/  m_MASK_INT_HOTPLUG ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 
 struct platform_device* to_platform_device (struct device*) ; 
 int /*<<< orphan*/  v_MASK_INT_HOTPLUG (int) ; 

__attribute__((used)) static int inno_hdmi_bind(struct device *dev, struct device *master,
				 void *data)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct drm_device *drm = data;
	struct inno_hdmi *hdmi;
	struct resource *iores;
	int irq;
	int ret;

	hdmi = devm_kzalloc(dev, sizeof(*hdmi), GFP_KERNEL);
	if (!hdmi)
		return -ENOMEM;

	hdmi->dev = dev;
	hdmi->drm_dev = drm;

	iores = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	hdmi->regs = devm_ioremap_resource(dev, iores);
	if (IS_ERR(hdmi->regs))
		return PTR_ERR(hdmi->regs);

	hdmi->pclk = devm_clk_get(hdmi->dev, "pclk");
	if (IS_ERR(hdmi->pclk)) {
		DRM_DEV_ERROR(hdmi->dev, "Unable to get HDMI pclk clk\n");
		return PTR_ERR(hdmi->pclk);
	}

	ret = clk_prepare_enable(hdmi->pclk);
	if (ret) {
		DRM_DEV_ERROR(hdmi->dev,
			      "Cannot enable HDMI pclk clock: %d\n", ret);
		return ret;
	}

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		ret = irq;
		goto err_disable_clk;
	}

	inno_hdmi_reset(hdmi);

	hdmi->ddc = inno_hdmi_i2c_adapter(hdmi);
	if (IS_ERR(hdmi->ddc)) {
		ret = PTR_ERR(hdmi->ddc);
		hdmi->ddc = NULL;
		goto err_disable_clk;
	}

	/*
	 * When IP controller haven't configured to an accurate video
	 * timing, then the TMDS clock source would be switched to
	 * PCLK_HDMI, so we need to init the TMDS rate to PCLK rate,
	 * and reconfigure the DDC clock.
	 */
	hdmi->tmds_rate = clk_get_rate(hdmi->pclk);
	inno_hdmi_i2c_init(hdmi);

	ret = inno_hdmi_register(drm, hdmi);
	if (ret)
		goto err_put_adapter;

	dev_set_drvdata(dev, hdmi);

	/* Unmute hotplug interrupt */
	hdmi_modb(hdmi, HDMI_STATUS, m_MASK_INT_HOTPLUG, v_MASK_INT_HOTPLUG(1));

	ret = devm_request_threaded_irq(dev, irq, inno_hdmi_hardirq,
					inno_hdmi_irq, IRQF_SHARED,
					dev_name(dev), hdmi);
	if (ret < 0)
		goto err_cleanup_hdmi;

	return 0;
err_cleanup_hdmi:
	hdmi->connector.funcs->destroy(&hdmi->connector);
	hdmi->encoder.funcs->destroy(&hdmi->encoder);
err_put_adapter:
	i2c_put_adapter(hdmi->ddc);
err_disable_clk:
	clk_disable_unprepare(hdmi->pclk);
	return ret;
}