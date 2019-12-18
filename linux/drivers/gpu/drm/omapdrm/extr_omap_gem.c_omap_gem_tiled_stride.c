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
typedef  int /*<<< orphan*/  u32 ;
struct omap_gem_object {int flags; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int OMAP_BO_TILED ; 
 int /*<<< orphan*/  gem2fmt (int) ; 
 int tiler_stride (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct omap_gem_object* to_omap_bo (struct drm_gem_object*) ; 

int omap_gem_tiled_stride(struct drm_gem_object *obj, u32 orient)
{
	struct omap_gem_object *omap_obj = to_omap_bo(obj);
	int ret = -EINVAL;
	if (omap_obj->flags & OMAP_BO_TILED)
		ret = tiler_stride(gem2fmt(omap_obj->flags), orient);
	return ret;
}