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
struct drm_gem_object {int dummy; } ;
struct etnaviv_gem_object {struct drm_gem_object base; int /*<<< orphan*/  pages; struct sg_table* sgt; int /*<<< orphan*/  lock; } ;
struct drm_device {int dummy; } ;
struct dma_buf_attachment {TYPE_1__* dmabuf; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct drm_gem_object* ERR_PTR (int) ; 
 int /*<<< orphan*/  ETNA_BO_WC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 int drm_prime_sg_to_page_addr_arrays (struct sg_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int etnaviv_gem_new_private (struct drm_device*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct etnaviv_gem_object**) ; 
 int /*<<< orphan*/  etnaviv_gem_obj_add (struct drm_device*,struct drm_gem_object*) ; 
 int /*<<< orphan*/  etnaviv_gem_prime_ops ; 
 int /*<<< orphan*/  etnaviv_prime_lock_class ; 
 int /*<<< orphan*/  kvmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_set_class (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct drm_gem_object *etnaviv_gem_prime_import_sg_table(struct drm_device *dev,
	struct dma_buf_attachment *attach, struct sg_table *sgt)
{
	struct etnaviv_gem_object *etnaviv_obj;
	size_t size = PAGE_ALIGN(attach->dmabuf->size);
	int ret, npages;

	ret = etnaviv_gem_new_private(dev, size, ETNA_BO_WC,
				      &etnaviv_gem_prime_ops, &etnaviv_obj);
	if (ret < 0)
		return ERR_PTR(ret);

	lockdep_set_class(&etnaviv_obj->lock, &etnaviv_prime_lock_class);

	npages = size / PAGE_SIZE;

	etnaviv_obj->sgt = sgt;
	etnaviv_obj->pages = kvmalloc_array(npages, sizeof(struct page *), GFP_KERNEL);
	if (!etnaviv_obj->pages) {
		ret = -ENOMEM;
		goto fail;
	}

	ret = drm_prime_sg_to_page_addr_arrays(sgt, etnaviv_obj->pages,
					       NULL, npages);
	if (ret)
		goto fail;

	etnaviv_gem_obj_add(dev, &etnaviv_obj->base);

	return &etnaviv_obj->base;

fail:
	drm_gem_object_put_unlocked(&etnaviv_obj->base);

	return ERR_PTR(ret);
}