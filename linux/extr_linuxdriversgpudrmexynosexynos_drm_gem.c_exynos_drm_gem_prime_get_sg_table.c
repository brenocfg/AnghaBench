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
struct exynos_drm_gem {int size; int /*<<< orphan*/  pages; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 struct sg_table* drm_prime_pages_to_sg (int /*<<< orphan*/ ,int) ; 
 struct exynos_drm_gem* to_exynos_gem (struct drm_gem_object*) ; 

struct sg_table *exynos_drm_gem_prime_get_sg_table(struct drm_gem_object *obj)
{
	struct exynos_drm_gem *exynos_gem = to_exynos_gem(obj);
	int npages;

	npages = exynos_gem->size >> PAGE_SHIFT;

	return drm_prime_pages_to_sg(exynos_gem->pages, npages);
}