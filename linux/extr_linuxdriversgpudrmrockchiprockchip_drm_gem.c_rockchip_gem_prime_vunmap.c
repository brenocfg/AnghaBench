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
struct rockchip_gem_object {scalar_t__ pages; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 struct rockchip_gem_object* to_rockchip_obj (struct drm_gem_object*) ; 
 int /*<<< orphan*/  vunmap (void*) ; 

void rockchip_gem_prime_vunmap(struct drm_gem_object *obj, void *vaddr)
{
	struct rockchip_gem_object *rk_obj = to_rockchip_obj(obj);

	if (rk_obj->pages) {
		vunmap(vaddr);
		return;
	}

	/* Nothing to do if allocated by DMA mapping API. */
}