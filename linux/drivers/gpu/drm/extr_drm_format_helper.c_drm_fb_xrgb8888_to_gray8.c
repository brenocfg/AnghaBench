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
typedef  int u8 ;
typedef  int u32 ;
struct drm_rect {int x2; int x1; unsigned int y1; unsigned int y2; } ;
struct drm_framebuffer {unsigned int* pitches; TYPE_1__* format; } ;
struct TYPE_2__ {scalar_t__ format; } ;

/* Variables and functions */
 scalar_t__ DRM_FORMAT_XRGB8888 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int*,unsigned int) ; 

void drm_fb_xrgb8888_to_gray8(u8 *dst, void *vaddr, struct drm_framebuffer *fb,
			       struct drm_rect *clip)
{
	unsigned int len = (clip->x2 - clip->x1) * sizeof(u32);
	unsigned int x, y;
	void *buf;
	u32 *src;

	if (WARN_ON(fb->format->format != DRM_FORMAT_XRGB8888))
		return;
	/*
	 * The cma memory is write-combined so reads are uncached.
	 * Speed up by fetching one line at a time.
	 */
	buf = kmalloc(len, GFP_KERNEL);
	if (!buf)
		return;

	for (y = clip->y1; y < clip->y2; y++) {
		src = vaddr + (y * fb->pitches[0]);
		src += clip->x1;
		memcpy(buf, src, len);
		src = buf;
		for (x = clip->x1; x < clip->x2; x++) {
			u8 r = (*src & 0x00ff0000) >> 16;
			u8 g = (*src & 0x0000ff00) >> 8;
			u8 b =  *src & 0x000000ff;

			/* ITU BT.601: Y = 0.299 R + 0.587 G + 0.114 B */
			*dst++ = (3 * r + 6 * g + b) / 10;
			src++;
		}
	}

	kfree(buf);
}