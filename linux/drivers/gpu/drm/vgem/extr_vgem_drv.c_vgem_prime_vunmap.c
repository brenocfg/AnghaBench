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
struct drm_vgem_gem_object {int dummy; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 struct drm_vgem_gem_object* to_vgem_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  vgem_unpin_pages (struct drm_vgem_gem_object*) ; 
 int /*<<< orphan*/  vunmap (void*) ; 

__attribute__((used)) static void vgem_prime_vunmap(struct drm_gem_object *obj, void *vaddr)
{
	struct drm_vgem_gem_object *bo = to_vgem_bo(obj);

	vunmap(vaddr);
	vgem_unpin_pages(bo);
}