#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_mode_fb_cmd2 {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct TYPE_3__ {int* dev_private; } ;

/* Variables and functions */
 struct drm_framebuffer* drm_internal_framebuffer_create (TYPE_1__*,struct drm_mode_fb_cmd2*,int /*<<< orphan*/ *) ; 
 TYPE_1__ mock_drm_device ; 

__attribute__((used)) static int execute_drm_mode_fb_cmd2(struct drm_mode_fb_cmd2 *r)
{
	int buffer_created = 0;
	struct drm_framebuffer *fb;

	mock_drm_device.dev_private = &buffer_created;
	fb = drm_internal_framebuffer_create(&mock_drm_device, r, NULL);
	return buffer_created;
}