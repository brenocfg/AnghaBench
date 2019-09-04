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
struct drm_framebuffer {unsigned int* pitches; TYPE_1__* format; } ;
struct drm_clip_rect {unsigned int y1; unsigned int x1; unsigned int x2; unsigned int y2; } ;
struct TYPE_2__ {int /*<<< orphan*/  format; } ;

/* Variables and functions */
 unsigned int drm_format_plane_cpp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 

void tinydrm_memcpy(void *dst, void *vaddr, struct drm_framebuffer *fb,
		    struct drm_clip_rect *clip)
{
	unsigned int cpp = drm_format_plane_cpp(fb->format->format, 0);
	unsigned int pitch = fb->pitches[0];
	void *src = vaddr + (clip->y1 * pitch) + (clip->x1 * cpp);
	size_t len = (clip->x2 - clip->x1) * cpp;
	unsigned int y;

	for (y = clip->y1; y < clip->y2; y++) {
		memcpy(dst, src, len);
		src += pitch;
		dst += len;
	}
}