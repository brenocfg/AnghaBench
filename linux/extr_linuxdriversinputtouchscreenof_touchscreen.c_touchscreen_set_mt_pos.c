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
struct touchscreen_properties {int dummy; } ;
struct input_mt_pos {unsigned int x; unsigned int y; } ;

/* Variables and functions */
 int /*<<< orphan*/  touchscreen_apply_prop_to_x_y (struct touchscreen_properties const*,unsigned int*,unsigned int*) ; 

void touchscreen_set_mt_pos(struct input_mt_pos *pos,
			    const struct touchscreen_properties *prop,
			    unsigned int x, unsigned int y)
{
	touchscreen_apply_prop_to_x_y(prop, &x, &y);
	pos->x = x;
	pos->y = y;
}