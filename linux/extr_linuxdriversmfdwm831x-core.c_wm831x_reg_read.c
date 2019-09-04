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
struct wm831x {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int regmap_read (int /*<<< orphan*/ ,unsigned short,unsigned int*) ; 

int wm831x_reg_read(struct wm831x *wm831x, unsigned short reg)
{
	unsigned int val;
	int ret;

	ret = regmap_read(wm831x->regmap, reg, &val);

	if (ret < 0)
		return ret;
	else
		return val;
}