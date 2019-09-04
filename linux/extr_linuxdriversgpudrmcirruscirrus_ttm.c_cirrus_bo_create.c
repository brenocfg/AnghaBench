#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_device {struct cirrus_device* dev_private; } ;
struct TYPE_3__ {int /*<<< orphan*/  bdev; } ;
struct cirrus_device {TYPE_1__ ttm; } ;
struct TYPE_4__ {int /*<<< orphan*/ * bdev; } ;
struct cirrus_bo {int /*<<< orphan*/  placement; TYPE_2__ bo; int /*<<< orphan*/  gem; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SHIFT ; 
 int TTM_PL_FLAG_SYSTEM ; 
 int TTM_PL_FLAG_VRAM ; 
 int /*<<< orphan*/  cirrus_bo_ttm_destroy ; 
 int /*<<< orphan*/  cirrus_ttm_placement (struct cirrus_bo*,int) ; 
 int drm_gem_object_init (struct drm_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct cirrus_bo*) ; 
 struct cirrus_bo* kzalloc (int,int /*<<< orphan*/ ) ; 
 size_t ttm_bo_dma_acc_size (int /*<<< orphan*/ *,int,int) ; 
 int ttm_bo_init (int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_bo_type_device ; 

int cirrus_bo_create(struct drm_device *dev, int size, int align,
		  uint32_t flags, struct cirrus_bo **pcirrusbo)
{
	struct cirrus_device *cirrus = dev->dev_private;
	struct cirrus_bo *cirrusbo;
	size_t acc_size;
	int ret;

	cirrusbo = kzalloc(sizeof(struct cirrus_bo), GFP_KERNEL);
	if (!cirrusbo)
		return -ENOMEM;

	ret = drm_gem_object_init(dev, &cirrusbo->gem, size);
	if (ret) {
		kfree(cirrusbo);
		return ret;
	}

	cirrusbo->bo.bdev = &cirrus->ttm.bdev;

	cirrus_ttm_placement(cirrusbo, TTM_PL_FLAG_VRAM | TTM_PL_FLAG_SYSTEM);

	acc_size = ttm_bo_dma_acc_size(&cirrus->ttm.bdev, size,
				       sizeof(struct cirrus_bo));

	ret = ttm_bo_init(&cirrus->ttm.bdev, &cirrusbo->bo, size,
			  ttm_bo_type_device, &cirrusbo->placement,
			  align >> PAGE_SHIFT, false, acc_size,
			  NULL, NULL, cirrus_bo_ttm_destroy);
	if (ret)
		return ret;

	*pcirrusbo = cirrusbo;
	return 0;
}