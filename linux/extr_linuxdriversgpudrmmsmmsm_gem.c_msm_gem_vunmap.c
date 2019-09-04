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
struct msm_gem_object {int /*<<< orphan*/  lock; } ;
struct drm_gem_object {int dummy; } ;
typedef  enum msm_gem_lock { ____Placeholder_msm_gem_lock } msm_gem_lock ;

/* Variables and functions */
 int /*<<< orphan*/  msm_gem_vunmap_locked (struct drm_gem_object*) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct msm_gem_object* to_msm_bo (struct drm_gem_object*) ; 

void msm_gem_vunmap(struct drm_gem_object *obj, enum msm_gem_lock subclass)
{
	struct msm_gem_object *msm_obj = to_msm_bo(obj);

	mutex_lock_nested(&msm_obj->lock, subclass);
	msm_gem_vunmap_locked(obj);
	mutex_unlock(&msm_obj->lock);
}