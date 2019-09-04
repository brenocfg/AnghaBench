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
typedef  int u32 ;
typedef  int u16 ;
struct drm_framebuffer {unsigned int* pitches; } ;
struct drm_clip_rect {int x2; int x1; unsigned int y1; unsigned int y2; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,size_t) ; 
 int /*<<< orphan*/  swab16 (int) ; 

void tinydrm_xrgb8888_to_rgb565(u16 *dst, void *vaddr,
				struct drm_framebuffer *fb,
				struct drm_clip_rect *clip, bool swap)
{
	size_t len = (clip->x2 - clip->x1) * sizeof(u32);
	unsigned int x, y;
	u32 *src, *buf;
	u16 val16;

	buf = kmalloc(len, GFP_KERNEL);
	if (!buf)
		return;

	for (y = clip->y1; y < clip->y2; y++) {
		src = vaddr + (y * fb->pitches[0]);
		src += clip->x1;
		memcpy(buf, src, len);
		src = buf;
		for (x = clip->x1; x < clip->x2; x++) {
			val16 = ((*src & 0x00F80000) >> 8) |
				((*src & 0x0000FC00) >> 5) |
				((*src & 0x000000F8) >> 3);
			src++;
			if (swap)
				*dst++ = swab16(val16);
			else
				*dst++ = val16;
		}
	}

	kfree(buf);
}