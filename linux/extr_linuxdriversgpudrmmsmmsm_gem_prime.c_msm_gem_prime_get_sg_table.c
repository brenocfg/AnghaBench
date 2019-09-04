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
struct sg_table {int dummy; } ;
struct msm_gem_object {int /*<<< orphan*/  pages; } ;
struct drm_gem_object {int size; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 scalar_t__ WARN_ON (int) ; 
 struct sg_table* drm_prime_pages_to_sg (int /*<<< orphan*/ ,int) ; 
 struct msm_gem_object* to_msm_bo (struct drm_gem_object*) ; 

struct sg_table *msm_gem_prime_get_sg_table(struct drm_gem_object *obj)
{
	struct msm_gem_object *msm_obj = to_msm_bo(obj);
	int npages = obj->size >> PAGE_SHIFT;

	if (WARN_ON(!msm_obj->pages))  /* should have already pinned! */
		return NULL;

	return drm_prime_pages_to_sg(msm_obj->pages, npages);
}