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
struct vmw_private {int capabilities; int /*<<< orphan*/  bdev; TYPE_2__* dev; } ;
struct vmw_cmdbuf_man {int has_pool; int using_mob; size_t size; int /*<<< orphan*/ * cmd_space; int /*<<< orphan*/  default_size; int /*<<< orphan*/  mm; int /*<<< orphan*/  map_obj; int /*<<< orphan*/  map; int /*<<< orphan*/  handle; struct vmw_private* dev_priv; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*,char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t PAGE_ALIGN (size_t) ; 
 size_t PAGE_SHIFT ; 
 int SVGA_CAP_DX ; 
 int /*<<< orphan*/  VMW_CMDBUF_INLINE_SIZE ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int ttm_bo_create (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int ttm_bo_kmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_type_device ; 
 int /*<<< orphan*/  ttm_kmap_obj_virtual (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  vmw_mob_ne_placement ; 

int vmw_cmdbuf_set_pool_size(struct vmw_cmdbuf_man *man,
			     size_t size, size_t default_size)
{
	struct vmw_private *dev_priv = man->dev_priv;
	bool dummy;
	int ret;

	if (man->has_pool)
		return -EINVAL;

	/* First, try to allocate a huge chunk of DMA memory */
	size = PAGE_ALIGN(size);
	man->map = dma_alloc_coherent(&dev_priv->dev->pdev->dev, size,
				      &man->handle, GFP_KERNEL);
	if (man->map) {
		man->using_mob = false;
	} else {
		/*
		 * DMA memory failed. If we can have command buffers in a
		 * MOB, try to use that instead. Note that this will
		 * actually call into the already enabled manager, when
		 * binding the MOB.
		 */
		if (!(dev_priv->capabilities & SVGA_CAP_DX))
			return -ENOMEM;

		ret = ttm_bo_create(&dev_priv->bdev, size, ttm_bo_type_device,
				    &vmw_mob_ne_placement, 0, false,
				    &man->cmd_space);
		if (ret)
			return ret;

		man->using_mob = true;
		ret = ttm_bo_kmap(man->cmd_space, 0, size >> PAGE_SHIFT,
				  &man->map_obj);
		if (ret)
			goto out_no_map;

		man->map = ttm_kmap_obj_virtual(&man->map_obj, &dummy);
	}

	man->size = size;
	drm_mm_init(&man->mm, 0, size >> PAGE_SHIFT);

	man->has_pool = true;

	/*
	 * For now, set the default size to VMW_CMDBUF_INLINE_SIZE to
	 * prevent deadlocks from happening when vmw_cmdbuf_space_pool()
	 * needs to wait for space and we block on further command
	 * submissions to be able to free up space.
	 */
	man->default_size = VMW_CMDBUF_INLINE_SIZE;
	DRM_INFO("Using command buffers with %s pool.\n",
		 (man->using_mob) ? "MOB" : "DMA");

	return 0;

out_no_map:
	if (man->using_mob) {
		ttm_bo_put(man->cmd_space);
		man->cmd_space = NULL;
	}

	return ret;
}