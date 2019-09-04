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
struct msm_gem_object {int /*<<< orphan*/  mm_list; int /*<<< orphan*/ * gpu; } ;
struct msm_drm_private {int /*<<< orphan*/  inactive_list; } ;
struct drm_gem_object {struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 struct msm_gem_object* to_msm_bo (struct drm_gem_object*) ; 

void msm_gem_move_to_inactive(struct drm_gem_object *obj)
{
	struct drm_device *dev = obj->dev;
	struct msm_drm_private *priv = dev->dev_private;
	struct msm_gem_object *msm_obj = to_msm_bo(obj);

	WARN_ON(!mutex_is_locked(&dev->struct_mutex));

	msm_obj->gpu = NULL;
	list_del_init(&msm_obj->mm_list);
	list_add_tail(&msm_obj->mm_list, &priv->inactive_list);
}