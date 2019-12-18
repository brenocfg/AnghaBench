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
struct drm_rect {unsigned int x2; unsigned int x1; unsigned int y2; unsigned int y1; } ;
struct drm_framebuffer {int /*<<< orphan*/ * pitches; TYPE_1__* format; } ;
struct TYPE_2__ {unsigned int* cpp; } ;

/* Variables and functions */
 int /*<<< orphan*/  clip_offset (struct drm_rect*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 

void drm_fb_memcpy(void *dst, void *vaddr, struct drm_framebuffer *fb,
		   struct drm_rect *clip)
{
	unsigned int cpp = fb->format->cpp[0];
	size_t len = (clip->x2 - clip->x1) * cpp;
	unsigned int y, lines = clip->y2 - clip->y1;

	vaddr += clip_offset(clip, fb->pitches[0], cpp);
	for (y = 0; y < lines; y++) {
		memcpy(dst, vaddr, len);
		vaddr += fb->pitches[0];
		dst += len;
	}
}