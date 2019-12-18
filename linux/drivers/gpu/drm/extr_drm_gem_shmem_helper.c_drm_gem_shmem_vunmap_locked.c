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
struct drm_gem_object {TYPE_1__* import_attach; } ;
struct drm_gem_shmem_object {scalar_t__ vmap_use_count; int /*<<< orphan*/ * vaddr; struct drm_gem_object base; } ;
struct TYPE_2__ {int /*<<< orphan*/  dmabuf; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dma_buf_vunmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_shmem_put_pages (struct drm_gem_shmem_object*) ; 
 int /*<<< orphan*/  vunmap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drm_gem_shmem_vunmap_locked(struct drm_gem_shmem_object *shmem)
{
	struct drm_gem_object *obj = &shmem->base;

	if (WARN_ON_ONCE(!shmem->vmap_use_count))
		return;

	if (--shmem->vmap_use_count > 0)
		return;

	if (obj->import_attach)
		dma_buf_vunmap(obj->import_attach->dmabuf, shmem->vaddr);
	else
		vunmap(shmem->vaddr);

	shmem->vaddr = NULL;
	drm_gem_shmem_put_pages(shmem);
}