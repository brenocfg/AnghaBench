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
struct touchscreen_properties {unsigned int max_x; unsigned int max_y; scalar_t__ swap_x_y; scalar_t__ invert_y; scalar_t__ invert_x; } ;

/* Variables and functions */
 int /*<<< orphan*/  swap (unsigned int,unsigned int) ; 

__attribute__((used)) static void
touchscreen_apply_prop_to_x_y(const struct touchscreen_properties *prop,
			      unsigned int *x, unsigned int *y)
{
	if (prop->invert_x)
		*x = prop->max_x - *x;

	if (prop->invert_y)
		*y = prop->max_y - *y;

	if (prop->swap_x_y)
		swap(*x, *y);
}