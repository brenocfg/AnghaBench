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
struct omap_gem_object {int flags; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 int OMAP_BO_CACHED ; 
 int OMAP_BO_CACHE_MASK ; 
 int OMAP_BO_MEM_SHMEM ; 
 struct omap_gem_object* to_omap_bo (struct drm_gem_object*) ; 

__attribute__((used)) static inline bool omap_gem_is_cached_coherent(struct drm_gem_object *obj)
{
	struct omap_gem_object *omap_obj = to_omap_bo(obj);

	return !((omap_obj->flags & OMAP_BO_MEM_SHMEM) &&
		((omap_obj->flags & OMAP_BO_CACHE_MASK) == OMAP_BO_CACHED));
}