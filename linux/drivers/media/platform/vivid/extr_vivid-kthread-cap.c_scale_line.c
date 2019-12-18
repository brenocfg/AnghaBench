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

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static void scale_line(const u8 *src, u8 *dst, unsigned srcw, unsigned dstw, unsigned twopixsize)
{
	/* Coarse scaling with Bresenham */
	unsigned int_part;
	unsigned fract_part;
	unsigned src_x = 0;
	unsigned error = 0;
	unsigned x;

	/*
	 * We always combine two pixels to prevent color bleed in the packed
	 * yuv case.
	 */
	srcw /= 2;
	dstw /= 2;
	int_part = srcw / dstw;
	fract_part = srcw % dstw;
	for (x = 0; x < dstw; x++, dst += twopixsize) {
		memcpy(dst, src + src_x * twopixsize, twopixsize);
		src_x += int_part;
		error += fract_part;
		if (error >= dstw) {
			error -= dstw;
			src_x++;
		}
	}
}