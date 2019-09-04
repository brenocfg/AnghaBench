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
struct vc4_dev {struct drm_device* dev; } ;
struct platform_device {int dummy; } ;
struct drm_device {struct vc4_dev* dev_private; } ;
struct device {int /*<<< orphan*/  coherent_dma_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct drm_device*) ; 
 int PTR_ERR (struct drm_device*) ; 
 int component_bind_all (struct device*,struct drm_device*) ; 
 int /*<<< orphan*/  component_unbind_all (struct device*,struct drm_device*) ; 
 struct vc4_dev* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct drm_device* drm_dev_alloc (int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int drm_dev_register (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_config_init (struct drm_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct drm_device*) ; 
 struct platform_device* to_platform_device (struct device*) ; 
 int /*<<< orphan*/  vc4_bo_cache_destroy (struct drm_device*) ; 
 int vc4_bo_cache_init (struct drm_device*) ; 
 int /*<<< orphan*/  vc4_drm_driver ; 
 int /*<<< orphan*/  vc4_gem_destroy (struct drm_device*) ; 
 int /*<<< orphan*/  vc4_gem_init (struct drm_device*) ; 
 int /*<<< orphan*/  vc4_kick_out_firmware_fb () ; 
 int /*<<< orphan*/  vc4_kms_load (struct drm_device*) ; 

__attribute__((used)) static int vc4_drm_bind(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct drm_device *drm;
	struct vc4_dev *vc4;
	int ret = 0;

	dev->coherent_dma_mask = DMA_BIT_MASK(32);

	vc4 = devm_kzalloc(dev, sizeof(*vc4), GFP_KERNEL);
	if (!vc4)
		return -ENOMEM;

	drm = drm_dev_alloc(&vc4_drm_driver, dev);
	if (IS_ERR(drm))
		return PTR_ERR(drm);
	platform_set_drvdata(pdev, drm);
	vc4->dev = drm;
	drm->dev_private = vc4;

	ret = vc4_bo_cache_init(drm);
	if (ret)
		goto dev_put;

	drm_mode_config_init(drm);

	vc4_gem_init(drm);

	ret = component_bind_all(dev, drm);
	if (ret)
		goto gem_destroy;

	vc4_kick_out_firmware_fb();

	ret = drm_dev_register(drm, 0);
	if (ret < 0)
		goto unbind_all;

	vc4_kms_load(drm);

	return 0;

unbind_all:
	component_unbind_all(dev, drm);
gem_destroy:
	vc4_gem_destroy(drm);
	vc4_bo_cache_destroy(drm);
dev_put:
	drm_dev_put(drm);
	return ret;
}