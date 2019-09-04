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
struct drm_framebuffer {int /*<<< orphan*/ * obj; } ;
struct drm_file {int dummy; } ;

/* Variables and functions */
 int drm_gem_handle_create (struct drm_file*,int /*<<< orphan*/ ,unsigned int*) ; 

int drm_gem_fb_create_handle(struct drm_framebuffer *fb, struct drm_file *file,
			     unsigned int *handle)
{
	return drm_gem_handle_create(file, fb->obj[0], handle);
}