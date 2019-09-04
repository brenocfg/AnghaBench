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
struct page {int dummy; } ;
struct omap_gem_object {int /*<<< orphan*/  lock; struct page** pages; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int omap_gem_attach_pages (struct drm_gem_object*) ; 
 struct omap_gem_object* to_omap_bo (struct drm_gem_object*) ; 

int omap_gem_get_pages(struct drm_gem_object *obj, struct page ***pages,
		bool remap)
{
	struct omap_gem_object *omap_obj = to_omap_bo(obj);
	int ret = 0;

	mutex_lock(&omap_obj->lock);

	if (remap) {
		ret = omap_gem_attach_pages(obj);
		if (ret)
			goto unlock;
	}

	if (!omap_obj->pages) {
		ret = -ENOMEM;
		goto unlock;
	}

	*pages = omap_obj->pages;

unlock:
	mutex_unlock(&omap_obj->lock);

	return ret;
}