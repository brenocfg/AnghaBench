#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct omap_gem_object {int width; } ;
struct omap_drm_usergart_entry {int obj_pgoff; int /*<<< orphan*/ * obj; } ;
struct omap_drm_private {TYPE_1__* usergart; } ;
struct drm_gem_object {TYPE_3__* dev; } ;
typedef  int loff_t ;
typedef  enum tiler_fmt { ____Placeholder_tiler_fmt } tiler_fmt ;
struct TYPE_6__ {TYPE_2__* anon_inode; struct omap_drm_private* dev_private; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_mapping; } ;
struct TYPE_4__ {int height; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int omap_gem_mmap_offset (struct drm_gem_object*) ; 
 struct omap_gem_object* to_omap_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  unmap_mapping_range (int /*<<< orphan*/ ,int,size_t,int) ; 

__attribute__((used)) static void omap_gem_evict_entry(struct drm_gem_object *obj,
		enum tiler_fmt fmt, struct omap_drm_usergart_entry *entry)
{
	struct omap_gem_object *omap_obj = to_omap_bo(obj);
	struct omap_drm_private *priv = obj->dev->dev_private;
	int n = priv->usergart[fmt].height;
	size_t size = PAGE_SIZE * n;
	loff_t off = omap_gem_mmap_offset(obj) +
			(entry->obj_pgoff << PAGE_SHIFT);
	const int m = DIV_ROUND_UP(omap_obj->width << fmt, PAGE_SIZE);

	if (m > 1) {
		int i;
		/* if stride > than PAGE_SIZE then sparse mapping: */
		for (i = n; i > 0; i--) {
			unmap_mapping_range(obj->dev->anon_inode->i_mapping,
					    off, PAGE_SIZE, 1);
			off += PAGE_SIZE * m;
		}
	} else {
		unmap_mapping_range(obj->dev->anon_inode->i_mapping,
				    off, size, 1);
	}

	entry->obj = NULL;
}