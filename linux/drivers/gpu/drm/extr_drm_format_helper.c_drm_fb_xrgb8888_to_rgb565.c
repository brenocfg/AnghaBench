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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct drm_rect {size_t x2; size_t x1; unsigned int y2; unsigned int y1; } ;
struct drm_framebuffer {int /*<<< orphan*/ * pitches; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  clip_offset (struct drm_rect*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drm_fb_xrgb8888_to_rgb565_line (void*,void*,size_t,int) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 

void drm_fb_xrgb8888_to_rgb565(void *dst, void *vaddr,
			       struct drm_framebuffer *fb,
			       struct drm_rect *clip, bool swab)
{
	size_t linepixels = clip->x2 - clip->x1;
	size_t src_len = linepixels * sizeof(u32);
	size_t dst_len = linepixels * sizeof(u16);
	unsigned y, lines = clip->y2 - clip->y1;
	void *sbuf;

	/*
	 * The cma memory is write-combined so reads are uncached.
	 * Speed up by fetching one line at a time.
	 */
	sbuf = kmalloc(src_len, GFP_KERNEL);
	if (!sbuf)
		return;

	vaddr += clip_offset(clip, fb->pitches[0], sizeof(u32));
	for (y = 0; y < lines; y++) {
		memcpy(sbuf, vaddr, src_len);
		drm_fb_xrgb8888_to_rgb565_line(dst, sbuf, linepixels, swab);
		vaddr += fb->pitches[0];
		dst += dst_len;
	}

	kfree(sbuf);
}