#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct TYPE_3__ {int x1; int y1; } ;
struct drm_plane_state {TYPE_1__ src; struct drm_framebuffer* fb; } ;
struct drm_framebuffer {unsigned int* pitches; scalar_t__* offsets; struct drm_format_info* format; } ;
struct drm_format_info {unsigned int num_planes; int* cpp; unsigned int vsub; unsigned int hsub; } ;
struct TYPE_4__ {scalar_t__ dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,unsigned int,unsigned int,unsigned int,int) ; 
 TYPE_2__* drm_fb_obj (struct drm_framebuffer*) ; 

void armada_drm_plane_calc(struct drm_plane_state *state, u32 addrs[2][3],
	u16 pitches[3], bool interlaced)
{
	struct drm_framebuffer *fb = state->fb;
	const struct drm_format_info *format = fb->format;
	unsigned int num_planes = format->num_planes;
	unsigned int x = state->src.x1 >> 16;
	unsigned int y = state->src.y1 >> 16;
	u32 addr = drm_fb_obj(fb)->dev_addr;
	int i;

	DRM_DEBUG_KMS("pitch %u x %d y %d bpp %d\n",
		      fb->pitches[0], x, y, format->cpp[0] * 8);

	if (num_planes > 3)
		num_planes = 3;

	addrs[0][0] = addr + fb->offsets[0] + y * fb->pitches[0] +
		      x * format->cpp[0];
	pitches[0] = fb->pitches[0];

	y /= format->vsub;
	x /= format->hsub;

	for (i = 1; i < num_planes; i++) {
		addrs[0][i] = addr + fb->offsets[i] + y * fb->pitches[i] +
			      x * format->cpp[i];
		pitches[i] = fb->pitches[i];
	}
	for (; i < 3; i++) {
		addrs[0][i] = 0;
		pitches[i] = 0;
	}
	if (interlaced) {
		for (i = 0; i < 3; i++) {
			addrs[1][i] = addrs[0][i] + pitches[i];
			pitches[i] *= 2;
		}
	} else {
		for (i = 0; i < 3; i++)
			addrs[1][i] = addrs[0][i];
	}
}