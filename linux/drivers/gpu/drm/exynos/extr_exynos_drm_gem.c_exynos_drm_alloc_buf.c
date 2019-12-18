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
struct sg_table {int dummy; } ;
struct page {int dummy; } ;
struct TYPE_2__ {struct drm_device* dev; } ;
struct exynos_drm_gem {unsigned long dma_attrs; int flags; unsigned int size; int /*<<< orphan*/  pages; scalar_t__ dma_addr; int /*<<< orphan*/  cookie; TYPE_1__ base; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 unsigned long DMA_ATTR_FORCE_CONTIGUOUS ; 
 unsigned long DMA_ATTR_NON_CONSISTENT ; 
 unsigned long DMA_ATTR_NO_KERNEL_MAPPING ; 
 unsigned long DMA_ATTR_WRITE_COMBINE ; 
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EXYNOS_BO_CACHABLE ; 
 int EXYNOS_BO_NONCONTIG ; 
 int EXYNOS_BO_WC ; 
 int GFP_KERNEL ; 
 unsigned int PAGE_SHIFT ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  dma_alloc_attrs (int /*<<< orphan*/ ,unsigned int,scalar_t__*,int,unsigned long) ; 
 int /*<<< orphan*/  dma_free_attrs (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,scalar_t__,unsigned long) ; 
 int dma_get_sgtable_attrs (int /*<<< orphan*/ ,struct sg_table*,int /*<<< orphan*/ ,scalar_t__,unsigned int,unsigned long) ; 
 scalar_t__ drm_prime_sg_to_page_addr_arrays (struct sg_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmalloc_array (unsigned int,int,int) ; 
 int /*<<< orphan*/  sg_free_table (struct sg_table*) ; 
 int /*<<< orphan*/  to_dma_dev (struct drm_device*) ; 

__attribute__((used)) static int exynos_drm_alloc_buf(struct exynos_drm_gem *exynos_gem)
{
	struct drm_device *dev = exynos_gem->base.dev;
	unsigned long attr;
	unsigned int nr_pages;
	struct sg_table sgt;
	int ret = -ENOMEM;

	if (exynos_gem->dma_addr) {
		DRM_DEV_DEBUG_KMS(to_dma_dev(dev), "already allocated.\n");
		return 0;
	}

	exynos_gem->dma_attrs = 0;

	/*
	 * if EXYNOS_BO_CONTIG, fully physically contiguous memory
	 * region will be allocated else physically contiguous
	 * as possible.
	 */
	if (!(exynos_gem->flags & EXYNOS_BO_NONCONTIG))
		exynos_gem->dma_attrs |= DMA_ATTR_FORCE_CONTIGUOUS;

	/*
	 * if EXYNOS_BO_WC or EXYNOS_BO_NONCACHABLE, writecombine mapping
	 * else cachable mapping.
	 */
	if (exynos_gem->flags & EXYNOS_BO_WC ||
			!(exynos_gem->flags & EXYNOS_BO_CACHABLE))
		attr = DMA_ATTR_WRITE_COMBINE;
	else
		attr = DMA_ATTR_NON_CONSISTENT;

	exynos_gem->dma_attrs |= attr;
	exynos_gem->dma_attrs |= DMA_ATTR_NO_KERNEL_MAPPING;

	nr_pages = exynos_gem->size >> PAGE_SHIFT;

	exynos_gem->pages = kvmalloc_array(nr_pages, sizeof(struct page *),
			GFP_KERNEL | __GFP_ZERO);
	if (!exynos_gem->pages) {
		DRM_DEV_ERROR(to_dma_dev(dev), "failed to allocate pages.\n");
		return -ENOMEM;
	}

	exynos_gem->cookie = dma_alloc_attrs(to_dma_dev(dev), exynos_gem->size,
					     &exynos_gem->dma_addr, GFP_KERNEL,
					     exynos_gem->dma_attrs);
	if (!exynos_gem->cookie) {
		DRM_DEV_ERROR(to_dma_dev(dev), "failed to allocate buffer.\n");
		goto err_free;
	}

	ret = dma_get_sgtable_attrs(to_dma_dev(dev), &sgt, exynos_gem->cookie,
				    exynos_gem->dma_addr, exynos_gem->size,
				    exynos_gem->dma_attrs);
	if (ret < 0) {
		DRM_DEV_ERROR(to_dma_dev(dev), "failed to get sgtable.\n");
		goto err_dma_free;
	}

	if (drm_prime_sg_to_page_addr_arrays(&sgt, exynos_gem->pages, NULL,
					     nr_pages)) {
		DRM_DEV_ERROR(to_dma_dev(dev), "invalid sgtable.\n");
		ret = -EINVAL;
		goto err_sgt_free;
	}

	sg_free_table(&sgt);

	DRM_DEV_DEBUG_KMS(to_dma_dev(dev), "dma_addr(0x%lx), size(0x%lx)\n",
			(unsigned long)exynos_gem->dma_addr, exynos_gem->size);

	return 0;

err_sgt_free:
	sg_free_table(&sgt);
err_dma_free:
	dma_free_attrs(to_dma_dev(dev), exynos_gem->size, exynos_gem->cookie,
		       exynos_gem->dma_addr, exynos_gem->dma_attrs);
err_free:
	kvfree(exynos_gem->pages);

	return ret;
}