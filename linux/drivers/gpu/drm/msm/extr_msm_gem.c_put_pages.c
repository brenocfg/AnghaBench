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
struct msm_gem_object {int flags; int /*<<< orphan*/ * pages; scalar_t__ sgt; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 int MSM_BO_UNCACHED ; 
 int MSM_BO_WC ; 
 int /*<<< orphan*/  drm_gem_put_pages (struct drm_gem_object*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  put_pages_vram (struct drm_gem_object*) ; 
 int /*<<< orphan*/  sg_free_table (scalar_t__) ; 
 int /*<<< orphan*/  sync_for_cpu (struct msm_gem_object*) ; 
 struct msm_gem_object* to_msm_bo (struct drm_gem_object*) ; 
 scalar_t__ use_pages (struct drm_gem_object*) ; 

__attribute__((used)) static void put_pages(struct drm_gem_object *obj)
{
	struct msm_gem_object *msm_obj = to_msm_bo(obj);

	if (msm_obj->pages) {
		if (msm_obj->sgt) {
			/* For non-cached buffers, ensure the new
			 * pages are clean because display controller,
			 * GPU, etc. are not coherent:
			 */
			if (msm_obj->flags & (MSM_BO_WC|MSM_BO_UNCACHED))
				sync_for_cpu(msm_obj);

			sg_free_table(msm_obj->sgt);
			kfree(msm_obj->sgt);
		}

		if (use_pages(obj))
			drm_gem_put_pages(obj, msm_obj->pages, true, false);
		else
			put_pages_vram(obj);

		msm_obj->pages = NULL;
	}
}