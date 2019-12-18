#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vc4_dev {int /*<<< orphan*/  bin_bo_lock; int /*<<< orphan*/  debugfs_list; struct drm_device* dev; } ;
struct platform_device {int dummy; } ;
struct drm_device {struct vc4_dev* dev_private; } ;
struct device_node {int dummy; } ;
struct device {int /*<<< orphan*/  coherent_dma_mask; } ;
struct TYPE_3__ {int /*<<< orphan*/  driver_features; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRIVER_RENDER ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct drm_device*) ; 
 int PTR_ERR (struct drm_device*) ; 
 int component_bind_all (struct device*,struct drm_device*) ; 
 int /*<<< orphan*/  component_unbind_all (struct device*,struct drm_device*) ; 
 struct vc4_dev* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct drm_device* drm_dev_alloc (TYPE_1__*,struct device*) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int drm_dev_register (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fb_helper_remove_conflicting_framebuffers (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  drm_fbdev_generic_setup (struct drm_device*,int) ; 
 int /*<<< orphan*/  drm_mode_config_init (struct drm_device*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_device_is_available (struct device_node*) ; 
 struct device_node* of_find_matching_node_and_match (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct drm_device*) ; 
 struct platform_device* to_platform_device (struct device*) ; 
 int /*<<< orphan*/  vc4_bo_cache_destroy (struct drm_device*) ; 
 int vc4_bo_cache_init (struct drm_device*) ; 
 TYPE_1__ vc4_drm_driver ; 
 int /*<<< orphan*/  vc4_gem_destroy (struct drm_device*) ; 
 int /*<<< orphan*/  vc4_gem_init (struct drm_device*) ; 
 int vc4_kms_load (struct drm_device*) ; 
 int /*<<< orphan*/  vc4_v3d_dt_match ; 

__attribute__((used)) static int vc4_drm_bind(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct drm_device *drm;
	struct vc4_dev *vc4;
	struct device_node *node;
	int ret = 0;

	dev->coherent_dma_mask = DMA_BIT_MASK(32);

	vc4 = devm_kzalloc(dev, sizeof(*vc4), GFP_KERNEL);
	if (!vc4)
		return -ENOMEM;

	/* If VC4 V3D is missing, don't advertise render nodes. */
	node = of_find_matching_node_and_match(NULL, vc4_v3d_dt_match, NULL);
	if (!node || !of_device_is_available(node))
		vc4_drm_driver.driver_features &= ~DRIVER_RENDER;
	of_node_put(node);

	drm = drm_dev_alloc(&vc4_drm_driver, dev);
	if (IS_ERR(drm))
		return PTR_ERR(drm);
	platform_set_drvdata(pdev, drm);
	vc4->dev = drm;
	drm->dev_private = vc4;
	INIT_LIST_HEAD(&vc4->debugfs_list);

	mutex_init(&vc4->bin_bo_lock);

	ret = vc4_bo_cache_init(drm);
	if (ret)
		goto dev_put;

	drm_mode_config_init(drm);

	vc4_gem_init(drm);

	ret = component_bind_all(dev, drm);
	if (ret)
		goto gem_destroy;

	drm_fb_helper_remove_conflicting_framebuffers(NULL, "vc4drmfb", false);

	ret = vc4_kms_load(drm);
	if (ret < 0)
		goto unbind_all;

	ret = drm_dev_register(drm, 0);
	if (ret < 0)
		goto unbind_all;

	drm_fbdev_generic_setup(drm, 16);

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