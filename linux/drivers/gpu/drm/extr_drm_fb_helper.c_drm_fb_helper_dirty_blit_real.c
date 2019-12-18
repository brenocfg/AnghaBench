#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_framebuffer {unsigned int* pitches; TYPE_1__* format; } ;
struct drm_fb_helper {TYPE_3__* buffer; TYPE_2__* fbdev; struct drm_framebuffer* fb; } ;
struct drm_clip_rect {unsigned int y1; unsigned int x1; unsigned int x2; unsigned int y2; } ;
struct TYPE_6__ {void* vaddr; } ;
struct TYPE_5__ {void* screen_buffer; } ;
struct TYPE_4__ {unsigned int* cpp; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 

__attribute__((used)) static void drm_fb_helper_dirty_blit_real(struct drm_fb_helper *fb_helper,
					  struct drm_clip_rect *clip)
{
	struct drm_framebuffer *fb = fb_helper->fb;
	unsigned int cpp = fb->format->cpp[0];
	size_t offset = clip->y1 * fb->pitches[0] + clip->x1 * cpp;
	void *src = fb_helper->fbdev->screen_buffer + offset;
	void *dst = fb_helper->buffer->vaddr + offset;
	size_t len = (clip->x2 - clip->x1) * cpp;
	unsigned int y;

	for (y = clip->y1; y < clip->y2; y++) {
		memcpy(dst, src, len);
		src += fb->pitches[0];
		dst += fb->pitches[0];
	}
}