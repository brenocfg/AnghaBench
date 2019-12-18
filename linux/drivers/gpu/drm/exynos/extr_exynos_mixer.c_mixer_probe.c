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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct mixer_drv_data {scalar_t__ has_sclk; scalar_t__ is_vp_enabled; int /*<<< orphan*/  version; } ;
struct mixer_context {int /*<<< orphan*/  flags; int /*<<< orphan*/  mxr_ver; struct device* dev; struct platform_device* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MXR_BIT_HAS_SCLK ; 
 int /*<<< orphan*/  MXR_BIT_VP_ENABLED ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int component_add (struct device*,int /*<<< orphan*/ *) ; 
 struct mixer_context* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mixer_component_ops ; 
 struct mixer_drv_data* of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mixer_context*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 

__attribute__((used)) static int mixer_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	const struct mixer_drv_data *drv;
	struct mixer_context *ctx;
	int ret;

	ctx = devm_kzalloc(&pdev->dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx) {
		DRM_DEV_ERROR(dev, "failed to alloc mixer context.\n");
		return -ENOMEM;
	}

	drv = of_device_get_match_data(dev);

	ctx->pdev = pdev;
	ctx->dev = dev;
	ctx->mxr_ver = drv->version;

	if (drv->is_vp_enabled)
		__set_bit(MXR_BIT_VP_ENABLED, &ctx->flags);
	if (drv->has_sclk)
		__set_bit(MXR_BIT_HAS_SCLK, &ctx->flags);

	platform_set_drvdata(pdev, ctx);

	ret = component_add(&pdev->dev, &mixer_component_ops);
	if (!ret)
		pm_runtime_enable(dev);

	return ret;
}