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
struct drm_framebuffer {int width; int* pitches; } ;

/* Variables and functions */
 int cirrus_convert_to (struct drm_framebuffer*) ; 

__attribute__((used)) static int cirrus_pitch(struct drm_framebuffer *fb)
{
	int convert_cpp = cirrus_convert_to(fb);

	if (convert_cpp)
		return convert_cpp * fb->width;
	return fb->pitches[0];
}