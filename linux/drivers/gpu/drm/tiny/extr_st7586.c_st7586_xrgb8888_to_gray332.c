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
typedef  int u8 ;
struct drm_rect {size_t x2; size_t x1; size_t y2; size_t y1; } ;
struct drm_framebuffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_fb_xrgb8888_to_gray8 (int*,void*,struct drm_framebuffer*,struct drm_rect*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int* st7586_lookup ; 

__attribute__((used)) static void st7586_xrgb8888_to_gray332(u8 *dst, void *vaddr,
				       struct drm_framebuffer *fb,
				       struct drm_rect *clip)
{
	size_t len = (clip->x2 - clip->x1) * (clip->y2 - clip->y1);
	unsigned int x, y;
	u8 *src, *buf, val;

	buf = kmalloc(len, GFP_KERNEL);
	if (!buf)
		return;

	drm_fb_xrgb8888_to_gray8(buf, vaddr, fb, clip);
	src = buf;

	for (y = clip->y1; y < clip->y2; y++) {
		for (x = clip->x1; x < clip->x2; x += 3) {
			val = st7586_lookup[*src++ >> 6] << 5;
			val |= st7586_lookup[*src++ >> 6] << 2;
			val |= st7586_lookup[*src++ >> 6] >> 1;
			*dst++ = val;
		}
	}

	kfree(buf);
}