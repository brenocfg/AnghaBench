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
struct drm_gem_object {int size; TYPE_1__* import_attach; } ;
struct drm_gem_shmem_object {void* vaddr; scalar_t__ vmap_use_count; int /*<<< orphan*/  pages; struct drm_gem_object base; } ;
struct TYPE_2__ {int /*<<< orphan*/  dmabuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int ENOMEM ; 
 void* ERR_PTR (int) ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  VM_MAP ; 
 void* dma_buf_vmap (int /*<<< orphan*/ ) ; 
 int drm_gem_shmem_get_pages (struct drm_gem_shmem_object*) ; 
 int /*<<< orphan*/  drm_gem_shmem_put_pages (struct drm_gem_shmem_object*) ; 
 int /*<<< orphan*/  pgprot_writecombine (int /*<<< orphan*/ ) ; 
 void* vmap (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *drm_gem_shmem_vmap_locked(struct drm_gem_shmem_object *shmem)
{
	struct drm_gem_object *obj = &shmem->base;
	int ret;

	if (shmem->vmap_use_count++ > 0)
		return shmem->vaddr;

	ret = drm_gem_shmem_get_pages(shmem);
	if (ret)
		goto err_zero_use;

	if (obj->import_attach)
		shmem->vaddr = dma_buf_vmap(obj->import_attach->dmabuf);
	else
		shmem->vaddr = vmap(shmem->pages, obj->size >> PAGE_SHIFT,
				    VM_MAP, pgprot_writecombine(PAGE_KERNEL));

	if (!shmem->vaddr) {
		DRM_DEBUG_KMS("Failed to vmap pages\n");
		ret = -ENOMEM;
		goto err_put_pages;
	}

	return shmem->vaddr;

err_put_pages:
	drm_gem_shmem_put_pages(shmem);
err_zero_use:
	shmem->vmap_use_count = 0;

	return ERR_PTR(ret);
}