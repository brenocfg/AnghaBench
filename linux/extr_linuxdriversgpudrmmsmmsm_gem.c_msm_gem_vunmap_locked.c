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
struct msm_gem_object {int /*<<< orphan*/ * vaddr; int /*<<< orphan*/  lock; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  is_vunmapable (struct msm_gem_object*) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 struct msm_gem_object* to_msm_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  vunmap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void msm_gem_vunmap_locked(struct drm_gem_object *obj)
{
	struct msm_gem_object *msm_obj = to_msm_bo(obj);

	WARN_ON(!mutex_is_locked(&msm_obj->lock));

	if (!msm_obj->vaddr || WARN_ON(!is_vunmapable(msm_obj)))
		return;

	vunmap(msm_obj->vaddr);
	msm_obj->vaddr = NULL;
}