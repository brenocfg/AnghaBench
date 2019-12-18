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
struct sg_table {int nents; int /*<<< orphan*/  sgl; } ;
struct page {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct exynos_drm_gem {int size; struct drm_gem_object base; int /*<<< orphan*/  pages; int /*<<< orphan*/  flags; struct sg_table* sgt; int /*<<< orphan*/  dma_addr; } ;
struct drm_device {int dummy; } ;
struct dma_buf_attachment {TYPE_1__* dmabuf; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct drm_gem_object* ERR_PTR (int) ; 
 int /*<<< orphan*/  EXYNOS_BO_CONTIG ; 
 int /*<<< orphan*/  EXYNOS_BO_NONCONTIG ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct exynos_drm_gem*) ; 
 int PAGE_SHIFT ; 
 int PTR_ERR (struct exynos_drm_gem*) ; 
 int /*<<< orphan*/  drm_gem_object_release (struct drm_gem_object*) ; 
 int drm_prime_sg_to_page_addr_arrays (struct sg_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct exynos_drm_gem* exynos_drm_gem_init (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct exynos_drm_gem*) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_dma_address (int /*<<< orphan*/ ) ; 

struct drm_gem_object *
exynos_drm_gem_prime_import_sg_table(struct drm_device *dev,
				     struct dma_buf_attachment *attach,
				     struct sg_table *sgt)
{
	struct exynos_drm_gem *exynos_gem;
	int npages;
	int ret;

	exynos_gem = exynos_drm_gem_init(dev, attach->dmabuf->size);
	if (IS_ERR(exynos_gem)) {
		ret = PTR_ERR(exynos_gem);
		return ERR_PTR(ret);
	}

	exynos_gem->dma_addr = sg_dma_address(sgt->sgl);

	npages = exynos_gem->size >> PAGE_SHIFT;
	exynos_gem->pages = kvmalloc_array(npages, sizeof(struct page *), GFP_KERNEL);
	if (!exynos_gem->pages) {
		ret = -ENOMEM;
		goto err;
	}

	ret = drm_prime_sg_to_page_addr_arrays(sgt, exynos_gem->pages, NULL,
					       npages);
	if (ret < 0)
		goto err_free_large;

	exynos_gem->sgt = sgt;

	if (sgt->nents == 1) {
		/* always physically continuous memory if sgt->nents is 1. */
		exynos_gem->flags |= EXYNOS_BO_CONTIG;
	} else {
		/*
		 * this case could be CONTIG or NONCONTIG type but for now
		 * sets NONCONTIG.
		 * TODO. we have to find a way that exporter can notify
		 * the type of its own buffer to importer.
		 */
		exynos_gem->flags |= EXYNOS_BO_NONCONTIG;
	}

	return &exynos_gem->base;

err_free_large:
	kvfree(exynos_gem->pages);
err:
	drm_gem_object_release(&exynos_gem->base);
	kfree(exynos_gem);
	return ERR_PTR(ret);
}