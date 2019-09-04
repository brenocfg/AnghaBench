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
struct drm_mode_create_dumb {int pitch; int width; int size; int height; int /*<<< orphan*/  handle; int /*<<< orphan*/  bpp; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int udl_gem_create (struct drm_file*,struct drm_device*,int,int /*<<< orphan*/ *) ; 

int udl_dumb_create(struct drm_file *file,
		    struct drm_device *dev,
		    struct drm_mode_create_dumb *args)
{
	args->pitch = args->width * DIV_ROUND_UP(args->bpp, 8);
	args->size = args->pitch * args->height;
	return udl_gem_create(file, dev,
			      args->size, &args->handle);
}