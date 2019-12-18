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
typedef  size_t u64 ;
struct panfrost_gem_object {int /*<<< orphan*/  node; int /*<<< orphan*/  is_heap; int /*<<< orphan*/ * mmu; scalar_t__ noexec; } ;
struct panfrost_file_priv {int /*<<< orphan*/  mm_lock; int /*<<< orphan*/  mm; int /*<<< orphan*/  mmu; } ;
struct drm_gem_object {size_t size; } ;
struct drm_file {struct panfrost_file_priv* driver_priv; } ;

/* Variables and functions */
 size_t PAGE_SHIFT ; 
 unsigned long PANFROST_BO_NOEXEC ; 
 size_t SZ_2M ; 
 int drm_mm_insert_node_generic (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,size_t,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mm_remove_node (int /*<<< orphan*/ *) ; 
 int panfrost_mmu_map (struct panfrost_gem_object*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct panfrost_gem_object* to_panfrost_bo (struct drm_gem_object*) ; 

__attribute__((used)) static int panfrost_gem_open(struct drm_gem_object *obj, struct drm_file *file_priv)
{
	int ret;
	size_t size = obj->size;
	u64 align;
	struct panfrost_gem_object *bo = to_panfrost_bo(obj);
	unsigned long color = bo->noexec ? PANFROST_BO_NOEXEC : 0;
	struct panfrost_file_priv *priv = file_priv->driver_priv;

	/*
	 * Executable buffers cannot cross a 16MB boundary as the program
	 * counter is 24-bits. We assume executable buffers will be less than
	 * 16MB and aligning executable buffers to their size will avoid
	 * crossing a 16MB boundary.
	 */
	if (!bo->noexec)
		align = size >> PAGE_SHIFT;
	else
		align = size >= SZ_2M ? SZ_2M >> PAGE_SHIFT : 0;

	bo->mmu = &priv->mmu;
	spin_lock(&priv->mm_lock);
	ret = drm_mm_insert_node_generic(&priv->mm, &bo->node,
					 size >> PAGE_SHIFT, align, color, 0);
	spin_unlock(&priv->mm_lock);
	if (ret)
		return ret;

	if (!bo->is_heap) {
		ret = panfrost_mmu_map(bo);
		if (ret) {
			spin_lock(&priv->mm_lock);
			drm_mm_remove_node(&bo->node);
			spin_unlock(&priv->mm_lock);
		}
	}
	return ret;
}