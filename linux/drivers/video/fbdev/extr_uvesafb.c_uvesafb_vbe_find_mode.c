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
struct uvesafb_par {int vbe_modes_cnt; TYPE_1__* vbe_modes; } ;
struct TYPE_2__ {int x_res; int y_res; int depth; } ;

/* Variables and functions */
 unsigned char UVESAFB_EXACT_DEPTH ; 
 unsigned char UVESAFB_EXACT_RES ; 
 int abs (int) ; 

__attribute__((used)) static int uvesafb_vbe_find_mode(struct uvesafb_par *par,
		int xres, int yres, int depth, unsigned char flags)
{
	int i, match = -1, h = 0, d = 0x7fffffff;

	for (i = 0; i < par->vbe_modes_cnt; i++) {
		h = abs(par->vbe_modes[i].x_res - xres) +
		    abs(par->vbe_modes[i].y_res - yres) +
		    abs(depth - par->vbe_modes[i].depth);

		/*
		 * We have an exact match in terms of resolution
		 * and depth.
		 */
		if (h == 0)
			return i;

		if (h < d || (h == d && par->vbe_modes[i].depth > depth)) {
			d = h;
			match = i;
		}
	}
	i = 1;

	if (flags & UVESAFB_EXACT_DEPTH &&
			par->vbe_modes[match].depth != depth)
		i = 0;

	if (flags & UVESAFB_EXACT_RES && d > 24)
		i = 0;

	if (i != 0)
		return match;
	else
		return -1;
}