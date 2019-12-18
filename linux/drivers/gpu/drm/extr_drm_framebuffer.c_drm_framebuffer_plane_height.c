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
struct TYPE_2__ {int num_planes; } ;

/* Variables and functions */
 int fb_plane_height (int,TYPE_1__*,int) ; 

int drm_framebuffer_plane_height(int height,
				 const struct drm_framebuffer *fb, int plane)
{
	if (plane >= fb->format->num_planes)
		return 0;

	return fb_plane_height(height, fb->format, plane);
}