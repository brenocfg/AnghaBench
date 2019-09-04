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
struct mtk_drm_gem_obj {int /*<<< orphan*/  base; } ;
struct drm_mode_create_dumb {int pitch; int width; int bpp; int size; int height; int /*<<< orphan*/  handle; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 scalar_t__ IS_ERR (struct mtk_drm_gem_obj*) ; 
 int PTR_ERR (struct mtk_drm_gem_obj*) ; 
 int drm_gem_handle_create (struct drm_file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ *) ; 
 struct mtk_drm_gem_obj* mtk_drm_gem_create (struct drm_device*,int,int) ; 
 int /*<<< orphan*/  mtk_drm_gem_free_object (int /*<<< orphan*/ *) ; 

int mtk_drm_gem_dumb_create(struct drm_file *file_priv, struct drm_device *dev,
			    struct drm_mode_create_dumb *args)
{
	struct mtk_drm_gem_obj *mtk_gem;
	int ret;

	args->pitch = DIV_ROUND_UP(args->width * args->bpp, 8);
	args->size = args->pitch * args->height;

	mtk_gem = mtk_drm_gem_create(dev, args->size, false);
	if (IS_ERR(mtk_gem))
		return PTR_ERR(mtk_gem);

	/*
	 * allocate a id of idr table where the obj is registered
	 * and handle has the id what user can see.
	 */
	ret = drm_gem_handle_create(file_priv, &mtk_gem->base, &args->handle);
	if (ret)
		goto err_handle_create;

	/* drop reference from allocate - handle holds it now. */
	drm_gem_object_put_unlocked(&mtk_gem->base);

	return 0;

err_handle_create:
	mtk_drm_gem_free_object(&mtk_gem->base);
	return ret;
}