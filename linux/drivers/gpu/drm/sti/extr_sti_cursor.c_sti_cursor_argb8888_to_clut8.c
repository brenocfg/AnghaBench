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
struct TYPE_2__ {int* base; } ;
struct sti_cursor {unsigned int height; unsigned int width; TYPE_1__ pixmap; } ;

/* Variables and functions */

__attribute__((used)) static void sti_cursor_argb8888_to_clut8(struct sti_cursor *cursor, u32 *src)
{
	u8  *dst = cursor->pixmap.base;
	unsigned int i, j;
	u32 a, r, g, b;

	for (i = 0; i < cursor->height; i++) {
		for (j = 0; j < cursor->width; j++) {
			/* Pick the 2 higher bits of each component */
			a = (*src >> 30) & 3;
			r = (*src >> 22) & 3;
			g = (*src >> 14) & 3;
			b = (*src >> 6) & 3;
			*dst = a << 6 | r << 4 | g << 2 | b;
			src++;
			dst++;
		}
	}
}