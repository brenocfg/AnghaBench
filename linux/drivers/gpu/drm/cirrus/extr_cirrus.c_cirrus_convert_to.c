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
struct drm_framebuffer {int* pitches; int width; TYPE_1__* format; } ;
struct TYPE_2__ {int* cpp; } ;

/* Variables and functions */
 int CIRRUS_MAX_PITCH ; 

__attribute__((used)) static int cirrus_convert_to(struct drm_framebuffer *fb)
{
	if (fb->format->cpp[0] == 4 && fb->pitches[0] > CIRRUS_MAX_PITCH) {
		if (fb->width * 3 <= CIRRUS_MAX_PITCH)
			/* convert from XR24 to RG24 */
			return 3;
		else
			/* convert from XR24 to RG16 */
			return 2;
	}
	return 0;
}