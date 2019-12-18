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
struct sti_cursor {unsigned short* clut; } ;

/* Variables and functions */

__attribute__((used)) static void sti_cursor_init(struct sti_cursor *cursor)
{
	unsigned short *base = cursor->clut;
	unsigned int a, r, g, b;

	/* Assign CLUT values, ARGB444 format */
	for (a = 0; a < 4; a++)
		for (r = 0; r < 4; r++)
			for (g = 0; g < 4; g++)
				for (b = 0; b < 4; b++)
					*base++ = (a * 5) << 12 |
						  (r * 5) << 8 |
						  (g * 5) << 4 |
						  (b * 5);
}