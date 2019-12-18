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
struct drm_mode_create_dumb {int width; int bpp; int /*<<< orphan*/  pitch; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DIV_ROUND_UP (int,int) ; 
 int drm_gem_cma_dumb_create_internal (struct drm_file*,struct drm_device*,struct drm_mode_create_dumb*) ; 

__attribute__((used)) static int drm_sun4i_gem_dumb_create(struct drm_file *file_priv,
				     struct drm_device *drm,
				     struct drm_mode_create_dumb *args)
{
	/* The hardware only allows even pitches for YUV buffers. */
	args->pitch = ALIGN(DIV_ROUND_UP(args->width * args->bpp, 8), 2);

	return drm_gem_cma_dumb_create_internal(file_priv, drm, args);
}