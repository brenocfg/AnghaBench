#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_device {TYPE_1__* anon_inode; struct bochs_device* dev_private; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev_mapping; } ;
struct TYPE_7__ {TYPE_3__ bdev; } ;
struct bochs_device {TYPE_2__ ttm; } ;
struct TYPE_9__ {TYPE_3__* bdev; } ;
struct bochs_bo {int /*<<< orphan*/  placement; TYPE_4__ bo; int /*<<< orphan*/  gem; } ;
struct TYPE_6__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SHIFT ; 
 int TTM_PL_FLAG_SYSTEM ; 
 int TTM_PL_FLAG_VRAM ; 
 int /*<<< orphan*/  bochs_bo_ttm_destroy ; 
 int /*<<< orphan*/  bochs_ttm_placement (struct bochs_bo*,int) ; 
 int drm_gem_object_init (struct drm_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct bochs_bo*) ; 
 struct bochs_bo* kzalloc (int,int /*<<< orphan*/ ) ; 
 size_t ttm_bo_dma_acc_size (TYPE_3__*,int,int) ; 
 int ttm_bo_init (TYPE_3__*,TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_bo_type_device ; 

__attribute__((used)) static int bochs_bo_create(struct drm_device *dev, int size, int align,
			   uint32_t flags, struct bochs_bo **pbochsbo)
{
	struct bochs_device *bochs = dev->dev_private;
	struct bochs_bo *bochsbo;
	size_t acc_size;
	int ret;

	bochsbo = kzalloc(sizeof(struct bochs_bo), GFP_KERNEL);
	if (!bochsbo)
		return -ENOMEM;

	ret = drm_gem_object_init(dev, &bochsbo->gem, size);
	if (ret) {
		kfree(bochsbo);
		return ret;
	}

	bochsbo->bo.bdev = &bochs->ttm.bdev;
	bochsbo->bo.bdev->dev_mapping = dev->anon_inode->i_mapping;

	bochs_ttm_placement(bochsbo, TTM_PL_FLAG_VRAM | TTM_PL_FLAG_SYSTEM);

	acc_size = ttm_bo_dma_acc_size(&bochs->ttm.bdev, size,
				       sizeof(struct bochs_bo));

	ret = ttm_bo_init(&bochs->ttm.bdev, &bochsbo->bo, size,
			  ttm_bo_type_device, &bochsbo->placement,
			  align >> PAGE_SHIFT, false, acc_size,
			  NULL, NULL, bochs_bo_ttm_destroy);
	if (ret)
		return ret;

	*pbochsbo = bochsbo;
	return 0;
}