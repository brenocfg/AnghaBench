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
struct drm_framebuffer {TYPE_1__* format; } ;
struct TYPE_2__ {int* cpp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 

__attribute__((used)) static int check_fb(struct drm_framebuffer *fb)
{
	if (!fb)
		return 0;

	switch (fb->format->cpp[0] * 8) {
	case 8:
	case 16:
	case 24:
	case 32:
		return 0;
	default:
		DRM_ERROR("Unknown color depth\n");
		return -EINVAL;
	}
}