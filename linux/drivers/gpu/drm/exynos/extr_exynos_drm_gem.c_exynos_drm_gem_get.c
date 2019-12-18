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
struct exynos_drm_gem {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;

/* Variables and functions */
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,unsigned int) ; 
 struct exynos_drm_gem* to_exynos_gem (struct drm_gem_object*) ; 

struct exynos_drm_gem *exynos_drm_gem_get(struct drm_file *filp,
					  unsigned int gem_handle)
{
	struct drm_gem_object *obj;

	obj = drm_gem_object_lookup(filp, gem_handle);
	if (!obj)
		return NULL;
	return to_exynos_gem(obj);
}