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
struct v3d_bo {int /*<<< orphan*/  pages; } ;
struct sg_table {int dummy; } ;
struct drm_gem_object {int size; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 struct sg_table* drm_prime_pages_to_sg (int /*<<< orphan*/ ,int) ; 
 struct v3d_bo* to_v3d_bo (struct drm_gem_object*) ; 

struct sg_table *
v3d_prime_get_sg_table(struct drm_gem_object *obj)
{
	struct v3d_bo *bo = to_v3d_bo(obj);
	int npages = obj->size >> PAGE_SHIFT;

	return drm_prime_pages_to_sg(bo->pages, npages);
}