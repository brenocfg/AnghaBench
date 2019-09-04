#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct msm_gem_object {int /*<<< orphan*/  pages; int /*<<< orphan*/  vram_node; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct msm_drm_private {TYPE_2__ vram; } ;
struct drm_gem_object {TYPE_1__* dev; } ;
struct TYPE_3__ {struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mm_remove_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct msm_gem_object* to_msm_bo (struct drm_gem_object*) ; 

__attribute__((used)) static void put_pages_vram(struct drm_gem_object *obj)
{
	struct msm_gem_object *msm_obj = to_msm_bo(obj);
	struct msm_drm_private *priv = obj->dev->dev_private;

	spin_lock(&priv->vram.lock);
	drm_mm_remove_node(msm_obj->vram_node);
	spin_unlock(&priv->vram.lock);

	kvfree(msm_obj->pages);
}