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
struct panfrost_gem_object {int /*<<< orphan*/  node; scalar_t__ is_mapped; } ;
struct panfrost_file_priv {int /*<<< orphan*/  mm_lock; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {struct panfrost_file_priv* driver_priv; } ;

/* Variables and functions */
 scalar_t__ drm_mm_node_allocated (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mm_remove_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panfrost_mmu_unmap (struct panfrost_gem_object*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct panfrost_gem_object* to_panfrost_bo (struct drm_gem_object*) ; 

__attribute__((used)) static void panfrost_gem_close(struct drm_gem_object *obj, struct drm_file *file_priv)
{
	struct panfrost_gem_object *bo = to_panfrost_bo(obj);
	struct panfrost_file_priv *priv = file_priv->driver_priv;

	if (bo->is_mapped)
		panfrost_mmu_unmap(bo);

	spin_lock(&priv->mm_lock);
	if (drm_mm_node_allocated(&bo->node))
		drm_mm_remove_node(&bo->node);
	spin_unlock(&priv->mm_lock);
}