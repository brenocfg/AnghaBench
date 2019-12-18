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
struct drm_mode_create_dumb {int pitch; int width; int bpp; int size; int height; int /*<<< orphan*/  handle; } ;
struct drm_gem_cma_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int PTR_ERR_OR_ZERO (struct drm_gem_cma_object*) ; 
 struct drm_gem_cma_object* drm_gem_cma_create_with_handle (struct drm_file*,struct drm_device*,int,int /*<<< orphan*/ *) ; 

int drm_gem_cma_dumb_create(struct drm_file *file_priv,
			    struct drm_device *drm,
			    struct drm_mode_create_dumb *args)
{
	struct drm_gem_cma_object *cma_obj;

	args->pitch = DIV_ROUND_UP(args->width * args->bpp, 8);
	args->size = args->pitch * args->height;

	cma_obj = drm_gem_cma_create_with_handle(file_priv, drm, args->size,
						 &args->handle);
	return PTR_ERR_OR_ZERO(cma_obj);
}