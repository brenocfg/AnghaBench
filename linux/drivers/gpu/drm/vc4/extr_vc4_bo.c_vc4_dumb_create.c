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
struct TYPE_2__ {int /*<<< orphan*/  base; } ;
struct vc4_bo {TYPE_1__ base; int /*<<< orphan*/  madv; } ;
struct drm_mode_create_dumb {int width; int bpp; int pitch; int size; int height; int /*<<< orphan*/  handle; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 scalar_t__ IS_ERR (struct vc4_bo*) ; 
 int PTR_ERR (struct vc4_bo*) ; 
 int /*<<< orphan*/  VC4_BO_TYPE_DUMB ; 
 int /*<<< orphan*/  VC4_MADV_WILLNEED ; 
 int drm_gem_handle_create (struct drm_file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ *) ; 
 struct vc4_bo* vc4_bo_create (struct drm_device*,int,int,int /*<<< orphan*/ ) ; 

int vc4_dumb_create(struct drm_file *file_priv,
		    struct drm_device *dev,
		    struct drm_mode_create_dumb *args)
{
	int min_pitch = DIV_ROUND_UP(args->width * args->bpp, 8);
	struct vc4_bo *bo = NULL;
	int ret;

	if (args->pitch < min_pitch)
		args->pitch = min_pitch;

	if (args->size < args->pitch * args->height)
		args->size = args->pitch * args->height;

	bo = vc4_bo_create(dev, args->size, false, VC4_BO_TYPE_DUMB);
	if (IS_ERR(bo))
		return PTR_ERR(bo);

	bo->madv = VC4_MADV_WILLNEED;

	ret = drm_gem_handle_create(file_priv, &bo->base.base, &args->handle);
	drm_gem_object_put_unlocked(&bo->base.base);

	return ret;
}