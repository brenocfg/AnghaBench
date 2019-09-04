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
struct drm_gem_cma_object {int /*<<< orphan*/ * vaddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dmabuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_buf_vunmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_cma_free_object (struct drm_gem_object*) ; 
 struct drm_gem_cma_object* to_drm_gem_cma_obj (struct drm_gem_object*) ; 

void tinydrm_gem_cma_free_object(struct drm_gem_object *gem_obj)
{
	if (gem_obj->import_attach) {
		struct drm_gem_cma_object *cma_obj;

		cma_obj = to_drm_gem_cma_obj(gem_obj);
		dma_buf_vunmap(gem_obj->import_attach->dmabuf, cma_obj->vaddr);
		cma_obj->vaddr = NULL;
	}

	drm_gem_cma_free_object(gem_obj);
}