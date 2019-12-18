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
struct zx_hdmi {void* xclk; struct device* dev; void* osc_clk; void* cec_clk; void* mmio; struct drm_device* drm; } ;
struct resource {int dummy; } ;
struct platform_device {int dummy; } ;
struct drm_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct zx_hdmi*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct zx_hdmi* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct zx_hdmi*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (struct device*) ; 
 int zx_hdmi_audio_register (struct zx_hdmi*) ; 
 int zx_hdmi_ddc_register (struct zx_hdmi*) ; 
 int /*<<< orphan*/  zx_hdmi_irq_handler ; 
 int /*<<< orphan*/  zx_hdmi_irq_thread ; 
 int zx_hdmi_register (struct drm_device*,struct zx_hdmi*) ; 

__attribute__((used)) static int zx_hdmi_bind(struct device *dev, struct device *master, void *data)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct drm_device *drm = data;
	struct resource *res;
	struct zx_hdmi *hdmi;
	int irq;
	int ret;

	hdmi = devm_kzalloc(dev, sizeof(*hdmi), GFP_KERNEL);
	if (!hdmi)
		return -ENOMEM;

	hdmi->dev = dev;
	hdmi->drm = drm;

	dev_set_drvdata(dev, hdmi);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	hdmi->mmio = devm_ioremap_resource(dev, res);
	if (IS_ERR(hdmi->mmio)) {
		ret = PTR_ERR(hdmi->mmio);
		DRM_DEV_ERROR(dev, "failed to remap hdmi region: %d\n", ret);
		return ret;
	}

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	hdmi->cec_clk = devm_clk_get(hdmi->dev, "osc_cec");
	if (IS_ERR(hdmi->cec_clk)) {
		ret = PTR_ERR(hdmi->cec_clk);
		DRM_DEV_ERROR(dev, "failed to get cec_clk: %d\n", ret);
		return ret;
	}

	hdmi->osc_clk = devm_clk_get(hdmi->dev, "osc_clk");
	if (IS_ERR(hdmi->osc_clk)) {
		ret = PTR_ERR(hdmi->osc_clk);
		DRM_DEV_ERROR(dev, "failed to get osc_clk: %d\n", ret);
		return ret;
	}

	hdmi->xclk = devm_clk_get(hdmi->dev, "xclk");
	if (IS_ERR(hdmi->xclk)) {
		ret = PTR_ERR(hdmi->xclk);
		DRM_DEV_ERROR(dev, "failed to get xclk: %d\n", ret);
		return ret;
	}

	ret = zx_hdmi_ddc_register(hdmi);
	if (ret) {
		DRM_DEV_ERROR(dev, "failed to register ddc: %d\n", ret);
		return ret;
	}

	ret = zx_hdmi_audio_register(hdmi);
	if (ret) {
		DRM_DEV_ERROR(dev, "failed to register audio: %d\n", ret);
		return ret;
	}

	ret = zx_hdmi_register(drm, hdmi);
	if (ret) {
		DRM_DEV_ERROR(dev, "failed to register hdmi: %d\n", ret);
		return ret;
	}

	ret = devm_request_threaded_irq(dev, irq, zx_hdmi_irq_handler,
					zx_hdmi_irq_thread, IRQF_SHARED,
					dev_name(dev), hdmi);
	if (ret) {
		DRM_DEV_ERROR(dev, "failed to request threaded irq: %d\n", ret);
		return ret;
	}

	return 0;
}