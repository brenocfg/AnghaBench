#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  mode; } ;
struct tegra_bo {int /*<<< orphan*/  gem; int /*<<< orphan*/  flags; TYPE_1__ tiling; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 unsigned long DRM_TEGRA_GEM_CREATE_BOTTOM_UP ; 
 unsigned long DRM_TEGRA_GEM_CREATE_TILED ; 
 struct tegra_bo* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct tegra_bo*) ; 
 int /*<<< orphan*/  TEGRA_BO_BOTTOM_UP ; 
 int /*<<< orphan*/  TEGRA_BO_TILING_MODE_TILED ; 
 int /*<<< orphan*/  drm_gem_object_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct tegra_bo*) ; 
 int tegra_bo_alloc (struct drm_device*,struct tegra_bo*) ; 
 struct tegra_bo* tegra_bo_alloc_object (struct drm_device*,size_t) ; 

struct tegra_bo *tegra_bo_create(struct drm_device *drm, size_t size,
				 unsigned long flags)
{
	struct tegra_bo *bo;
	int err;

	bo = tegra_bo_alloc_object(drm, size);
	if (IS_ERR(bo))
		return bo;

	err = tegra_bo_alloc(drm, bo);
	if (err < 0)
		goto release;

	if (flags & DRM_TEGRA_GEM_CREATE_TILED)
		bo->tiling.mode = TEGRA_BO_TILING_MODE_TILED;

	if (flags & DRM_TEGRA_GEM_CREATE_BOTTOM_UP)
		bo->flags |= TEGRA_BO_BOTTOM_UP;

	return bo;

release:
	drm_gem_object_release(&bo->gem);
	kfree(bo);
	return ERR_PTR(err);
}