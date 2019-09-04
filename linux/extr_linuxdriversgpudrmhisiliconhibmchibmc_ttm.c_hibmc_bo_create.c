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
typedef  int /*<<< orphan*/  u32 ;
struct hibmc_drm_private {int /*<<< orphan*/  bdev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * bdev; } ;
struct hibmc_bo {int /*<<< orphan*/  placement; TYPE_1__ bo; int /*<<< orphan*/  gem; } ;
struct drm_device {struct hibmc_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SHIFT ; 
 int TTM_PL_FLAG_SYSTEM ; 
 int TTM_PL_FLAG_VRAM ; 
 int drm_gem_object_init (struct drm_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hibmc_bo_ttm_destroy ; 
 int /*<<< orphan*/  hibmc_bo_unref (struct hibmc_bo**) ; 
 int /*<<< orphan*/  hibmc_ttm_placement (struct hibmc_bo*,int) ; 
 int /*<<< orphan*/  kfree (struct hibmc_bo*) ; 
 struct hibmc_bo* kzalloc (int,int /*<<< orphan*/ ) ; 
 size_t ttm_bo_dma_acc_size (int /*<<< orphan*/ *,int,int) ; 
 int ttm_bo_init (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_bo_type_device ; 

int hibmc_bo_create(struct drm_device *dev, int size, int align,
		    u32 flags, struct hibmc_bo **phibmcbo)
{
	struct hibmc_drm_private *hibmc = dev->dev_private;
	struct hibmc_bo *hibmcbo;
	size_t acc_size;
	int ret;

	hibmcbo = kzalloc(sizeof(*hibmcbo), GFP_KERNEL);
	if (!hibmcbo) {
		DRM_ERROR("failed to allocate hibmcbo\n");
		return -ENOMEM;
	}
	ret = drm_gem_object_init(dev, &hibmcbo->gem, size);
	if (ret) {
		DRM_ERROR("failed to initialize drm gem object: %d\n", ret);
		kfree(hibmcbo);
		return ret;
	}

	hibmcbo->bo.bdev = &hibmc->bdev;

	hibmc_ttm_placement(hibmcbo, TTM_PL_FLAG_VRAM | TTM_PL_FLAG_SYSTEM);

	acc_size = ttm_bo_dma_acc_size(&hibmc->bdev, size,
				       sizeof(struct hibmc_bo));

	ret = ttm_bo_init(&hibmc->bdev, &hibmcbo->bo, size,
			  ttm_bo_type_device, &hibmcbo->placement,
			  align >> PAGE_SHIFT, false, acc_size,
			  NULL, NULL, hibmc_bo_ttm_destroy);
	if (ret) {
		hibmc_bo_unref(&hibmcbo);
		DRM_ERROR("failed to initialize ttm_bo: %d\n", ret);
		return ret;
	}

	*phibmcbo = hibmcbo;
	return 0;
}