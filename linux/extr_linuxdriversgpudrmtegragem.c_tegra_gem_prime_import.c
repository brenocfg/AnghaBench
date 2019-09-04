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
struct drm_gem_object {struct drm_device* dev; } ;
struct tegra_bo {struct drm_gem_object gem; } ;
struct drm_device {int dummy; } ;
struct dma_buf {struct drm_gem_object* priv; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 struct drm_gem_object* ERR_CAST (struct tegra_bo*) ; 
 scalar_t__ IS_ERR (struct tegra_bo*) ; 
 int /*<<< orphan*/  drm_gem_object_get (struct drm_gem_object*) ; 
 struct tegra_bo* tegra_bo_import (struct drm_device*,struct dma_buf*) ; 
 int /*<<< orphan*/  tegra_gem_prime_dmabuf_ops ; 

struct drm_gem_object *tegra_gem_prime_import(struct drm_device *drm,
					      struct dma_buf *buf)
{
	struct tegra_bo *bo;

	if (buf->ops == &tegra_gem_prime_dmabuf_ops) {
		struct drm_gem_object *gem = buf->priv;

		if (gem->dev == drm) {
			drm_gem_object_get(gem);
			return gem;
		}
	}

	bo = tegra_bo_import(drm, buf);
	if (IS_ERR(bo))
		return ERR_CAST(bo);

	return &bo->gem;
}