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
struct w8001 {unsigned int max_pen_x; unsigned int max_touch_x; unsigned int max_pen_y; unsigned int max_touch_y; } ;

/* Variables and functions */

__attribute__((used)) static void scale_touch_coordinates(struct w8001 *w8001,
				    unsigned int *x, unsigned int *y)
{
	if (w8001->max_pen_x && w8001->max_touch_x)
		*x = *x * w8001->max_pen_x / w8001->max_touch_x;

	if (w8001->max_pen_y && w8001->max_touch_y)
		*y = *y * w8001->max_pen_y / w8001->max_touch_y;
}