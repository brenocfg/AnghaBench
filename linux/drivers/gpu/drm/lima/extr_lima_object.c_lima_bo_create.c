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
typedef  int /*<<< orphan*/  u32 ;
struct sg_table {int dummy; } ;
struct lima_device {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {size_t size; TYPE_1__* filp; } ;
struct lima_bo {int /*<<< orphan*/ * pages_dma_addr; struct lima_bo* pages; TYPE_2__ gem; struct sg_table* sgt; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {int /*<<< orphan*/  f_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int EFAULT ; 
 int ENOMEM ; 
 struct lima_bo* ERR_CAST (struct lima_bo*) ; 
 struct lima_bo* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_DMA32 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct lima_bo*) ; 
 size_t PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_map_page (int /*<<< orphan*/ ,struct lima_bo,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct lima_bo* drm_gem_get_pages (TYPE_2__*) ; 
 int drm_prime_sg_to_page_addr_arrays (struct sg_table*,struct lima_bo*,int /*<<< orphan*/ *,size_t) ; 
 void* kcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 struct lima_bo* lima_bo_create_struct (struct lima_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lima_bo_destroy (struct lima_bo*) ; 
 int /*<<< orphan*/  mapping_set_gfp_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct lima_bo *lima_bo_create(struct lima_device *dev, u32 size,
			       u32 flags, struct sg_table *sgt)
{
	int i, err;
	size_t npages;
	struct lima_bo *bo, *ret;

	bo = lima_bo_create_struct(dev, size, flags);
	if (IS_ERR(bo))
		return bo;

	npages = bo->gem.size >> PAGE_SHIFT;

	bo->pages_dma_addr = kcalloc(npages, sizeof(dma_addr_t), GFP_KERNEL);
	if (!bo->pages_dma_addr) {
		ret = ERR_PTR(-ENOMEM);
		goto err_out;
	}

	if (sgt) {
		bo->sgt = sgt;

		bo->pages = kcalloc(npages, sizeof(*bo->pages), GFP_KERNEL);
		if (!bo->pages) {
			ret = ERR_PTR(-ENOMEM);
			goto err_out;
		}

		err = drm_prime_sg_to_page_addr_arrays(
			sgt, bo->pages, bo->pages_dma_addr, npages);
		if (err) {
			ret = ERR_PTR(err);
			goto err_out;
		}
	} else {
		mapping_set_gfp_mask(bo->gem.filp->f_mapping, GFP_DMA32);
		bo->pages = drm_gem_get_pages(&bo->gem);
		if (IS_ERR(bo->pages)) {
			ret = ERR_CAST(bo->pages);
			bo->pages = NULL;
			goto err_out;
		}

		for (i = 0; i < npages; i++) {
			dma_addr_t addr = dma_map_page(dev->dev, bo->pages[i], 0,
						       PAGE_SIZE, DMA_BIDIRECTIONAL);
			if (dma_mapping_error(dev->dev, addr)) {
				ret = ERR_PTR(-EFAULT);
				goto err_out;
			}
			bo->pages_dma_addr[i] = addr;
		}

	}

	return bo;

err_out:
	lima_bo_destroy(bo);
	return ret;
}