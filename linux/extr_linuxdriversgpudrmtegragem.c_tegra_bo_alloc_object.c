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
struct tegra_bo {int /*<<< orphan*/  gem; int /*<<< orphan*/  base; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct tegra_bo* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int drm_gem_create_mmap_offset (int /*<<< orphan*/ *) ; 
 int drm_gem_object_init (struct drm_device*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  drm_gem_object_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  host1x_bo_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct tegra_bo*) ; 
 struct tegra_bo* kzalloc (int,int /*<<< orphan*/ ) ; 
 size_t round_up (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_bo_ops ; 

__attribute__((used)) static struct tegra_bo *tegra_bo_alloc_object(struct drm_device *drm,
					      size_t size)
{
	struct tegra_bo *bo;
	int err;

	bo = kzalloc(sizeof(*bo), GFP_KERNEL);
	if (!bo)
		return ERR_PTR(-ENOMEM);

	host1x_bo_init(&bo->base, &tegra_bo_ops);
	size = round_up(size, PAGE_SIZE);

	err = drm_gem_object_init(drm, &bo->gem, size);
	if (err < 0)
		goto free;

	err = drm_gem_create_mmap_offset(&bo->gem);
	if (err < 0)
		goto release;

	return bo;

release:
	drm_gem_object_release(&bo->gem);
free:
	kfree(bo);
	return ERR_PTR(err);
}