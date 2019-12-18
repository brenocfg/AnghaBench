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
struct etnaviv_gem_object {int /*<<< orphan*/  gem_node; } ;
struct etnaviv_drm_private {int /*<<< orphan*/  gem_lock; int /*<<< orphan*/  gem_list; } ;
struct drm_gem_object {int dummy; } ;
struct drm_device {struct etnaviv_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct etnaviv_gem_object* to_etnaviv_bo (struct drm_gem_object*) ; 

void etnaviv_gem_obj_add(struct drm_device *dev, struct drm_gem_object *obj)
{
	struct etnaviv_drm_private *priv = dev->dev_private;
	struct etnaviv_gem_object *etnaviv_obj = to_etnaviv_bo(obj);

	mutex_lock(&priv->gem_lock);
	list_add_tail(&etnaviv_obj->gem_node, &priv->gem_list);
	mutex_unlock(&priv->gem_lock);
}