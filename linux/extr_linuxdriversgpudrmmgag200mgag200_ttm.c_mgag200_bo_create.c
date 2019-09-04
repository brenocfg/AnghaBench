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
struct TYPE_4__ {int /*<<< orphan*/ * bdev; } ;
struct mgag200_bo {int /*<<< orphan*/  placement; TYPE_2__ bo; int /*<<< orphan*/  gem; } ;
struct TYPE_3__ {int /*<<< orphan*/  bdev; } ;
struct mga_device {TYPE_1__ ttm; } ;
struct drm_device {struct mga_device* dev_private; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SHIFT ; 
 int TTM_PL_FLAG_SYSTEM ; 
 int TTM_PL_FLAG_VRAM ; 
 int drm_gem_object_init (struct drm_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct mgag200_bo*) ; 
 struct mgag200_bo* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgag200_bo_ttm_destroy ; 
 int /*<<< orphan*/  mgag200_ttm_placement (struct mgag200_bo*,int) ; 
 size_t ttm_bo_dma_acc_size (int /*<<< orphan*/ *,int,int) ; 
 int ttm_bo_init (int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_bo_type_device ; 

int mgag200_bo_create(struct drm_device *dev, int size, int align,
		  uint32_t flags, struct mgag200_bo **pmgabo)
{
	struct mga_device *mdev = dev->dev_private;
	struct mgag200_bo *mgabo;
	size_t acc_size;
	int ret;

	mgabo = kzalloc(sizeof(struct mgag200_bo), GFP_KERNEL);
	if (!mgabo)
		return -ENOMEM;

	ret = drm_gem_object_init(dev, &mgabo->gem, size);
	if (ret) {
		kfree(mgabo);
		return ret;
	}

	mgabo->bo.bdev = &mdev->ttm.bdev;

	mgag200_ttm_placement(mgabo, TTM_PL_FLAG_VRAM | TTM_PL_FLAG_SYSTEM);

	acc_size = ttm_bo_dma_acc_size(&mdev->ttm.bdev, size,
				       sizeof(struct mgag200_bo));

	ret = ttm_bo_init(&mdev->ttm.bdev, &mgabo->bo, size,
			  ttm_bo_type_device, &mgabo->placement,
			  align >> PAGE_SHIFT, false, acc_size,
			  NULL, NULL, mgag200_bo_ttm_destroy);
	if (ret)
		return ret;

	*pmgabo = mgabo;
	return 0;
}