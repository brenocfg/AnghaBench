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
struct drm_gem_shmem_object {int pages_use_count; struct drm_gem_object base; int /*<<< orphan*/  pages; struct sg_table* sgt; } ;
struct drm_device {int dummy; } ;
struct dma_buf_attachment {TYPE_1__* dmabuf; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_PRIME (char*,size_t) ; 
 int ENOMEM ; 
 struct drm_gem_object* ERR_CAST (struct drm_gem_shmem_object*) ; 
 struct drm_gem_object* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct drm_gem_shmem_object*) ; 
 size_t PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 size_t PAGE_SHIFT ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 struct drm_gem_shmem_object* drm_gem_shmem_create (struct drm_device*,size_t) ; 
 int drm_prime_sg_to_page_addr_arrays (struct sg_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmalloc_array (size_t,int,int /*<<< orphan*/ ) ; 

struct drm_gem_object *
drm_gem_shmem_prime_import_sg_table(struct drm_device *dev,
				    struct dma_buf_attachment *attach,
				    struct sg_table *sgt)
{
	size_t size = PAGE_ALIGN(attach->dmabuf->size);
	size_t npages = size >> PAGE_SHIFT;
	struct drm_gem_shmem_object *shmem;
	int ret;

	shmem = drm_gem_shmem_create(dev, size);
	if (IS_ERR(shmem))
		return ERR_CAST(shmem);

	shmem->pages = kvmalloc_array(npages, sizeof(struct page *), GFP_KERNEL);
	if (!shmem->pages) {
		ret = -ENOMEM;
		goto err_free_gem;
	}

	ret = drm_prime_sg_to_page_addr_arrays(sgt, shmem->pages, NULL, npages);
	if (ret < 0)
		goto err_free_array;

	shmem->sgt = sgt;
	shmem->pages_use_count = 1; /* Permanently pinned from our point of view */

	DRM_DEBUG_PRIME("size = %zu\n", size);

	return &shmem->base;

err_free_array:
	kvfree(shmem->pages);
err_free_gem:
	drm_gem_object_put_unlocked(&shmem->base);

	return ERR_PTR(ret);
}