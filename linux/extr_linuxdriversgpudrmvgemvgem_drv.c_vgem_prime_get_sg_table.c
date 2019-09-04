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
struct TYPE_2__ {int size; } ;
struct drm_vgem_gem_object {TYPE_1__ base; int /*<<< orphan*/  pages; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 struct sg_table* drm_prime_pages_to_sg (int /*<<< orphan*/ ,int) ; 
 struct drm_vgem_gem_object* to_vgem_bo (struct drm_gem_object*) ; 

__attribute__((used)) static struct sg_table *vgem_prime_get_sg_table(struct drm_gem_object *obj)
{
	struct drm_vgem_gem_object *bo = to_vgem_bo(obj);

	return drm_prime_pages_to_sg(bo->pages, bo->base.size >> PAGE_SHIFT);
}