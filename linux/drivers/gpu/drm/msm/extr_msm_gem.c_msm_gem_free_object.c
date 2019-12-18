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
struct msm_gem_object {int /*<<< orphan*/  freed; } ;
struct msm_drm_private {int /*<<< orphan*/  free_work; int /*<<< orphan*/  wq; int /*<<< orphan*/  free_list; } ;
struct drm_gem_object {struct drm_device* dev; } ;
struct drm_device {struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 scalar_t__ llist_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct msm_gem_object* to_msm_bo (struct drm_gem_object*) ; 

void msm_gem_free_object(struct drm_gem_object *obj)
{
	struct msm_gem_object *msm_obj = to_msm_bo(obj);
	struct drm_device *dev = obj->dev;
	struct msm_drm_private *priv = dev->dev_private;

	if (llist_add(&msm_obj->freed, &priv->free_list))
		queue_work(priv->wq, &priv->free_work);
}