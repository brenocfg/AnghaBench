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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static void drm_fb_xrgb8888_to_rgb888_line(u8 *dbuf, u32 *sbuf,
					   unsigned int pixels)
{
	unsigned int x;

	for (x = 0; x < pixels; x++) {
		*dbuf++ = (sbuf[x] & 0x000000FF) >>  0;
		*dbuf++ = (sbuf[x] & 0x0000FF00) >>  8;
		*dbuf++ = (sbuf[x] & 0x00FF0000) >> 16;
	}
}