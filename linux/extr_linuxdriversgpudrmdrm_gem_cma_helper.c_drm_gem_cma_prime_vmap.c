#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct drm_gem_object {int dummy; } ;
struct drm_gem_cma_object {void* vaddr; } ;

/* Variables and functions */
 struct drm_gem_cma_object* to_drm_gem_cma_obj (struct drm_gem_object*) ; 

void *drm_gem_cma_prime_vmap(struct drm_gem_object *obj)
{
	struct drm_gem_cma_object *cma_obj = to_drm_gem_cma_obj(obj);

	return cma_obj->vaddr;
}