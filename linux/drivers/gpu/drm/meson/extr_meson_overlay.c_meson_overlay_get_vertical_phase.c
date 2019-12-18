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

/* Variables and functions */
 int* skip_tab ; 

__attribute__((used)) static void meson_overlay_get_vertical_phase(unsigned int ratio_y, int *phase,
					     int *repeat, bool interlace)
{
	int offset_in = 0;
	int offset_out = 0;
	int repeat_skip = 0;

	if (!interlace && ratio_y > (1 << 18))
		offset_out = (1 * ratio_y) >> 10;

	while ((offset_in + (4 << 8)) <= offset_out) {
		repeat_skip++;
		offset_in += 4 << 8;
	}

	*phase = (offset_out - offset_in) >> 2;

	if (*phase > 0x100)
		repeat_skip++;

	*phase = *phase & 0xff;

	if (repeat_skip > 5)
		repeat_skip = 5;

	*repeat = skip_tab[repeat_skip];
}