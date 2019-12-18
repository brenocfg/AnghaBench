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
struct ttm_bo_device {int dummy; } ;
struct drm_gem_vram_object {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct drm_gem_vram_object* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int drm_gem_vram_init (struct drm_device*,struct ttm_bo_device*,struct drm_gem_vram_object*,size_t,unsigned long,int) ; 
 int /*<<< orphan*/  kfree (struct drm_gem_vram_object*) ; 
 struct drm_gem_vram_object* kzalloc (int,int /*<<< orphan*/ ) ; 

struct drm_gem_vram_object *drm_gem_vram_create(struct drm_device *dev,
						struct ttm_bo_device *bdev,
						size_t size,
						unsigned long pg_align,
						bool interruptible)
{
	struct drm_gem_vram_object *gbo;
	int ret;

	gbo = kzalloc(sizeof(*gbo), GFP_KERNEL);
	if (!gbo)
		return ERR_PTR(-ENOMEM);

	ret = drm_gem_vram_init(dev, bdev, gbo, size, pg_align, interruptible);
	if (ret < 0)
		goto err_kfree;

	return gbo;

err_kfree:
	kfree(gbo);
	return ERR_PTR(ret);
}