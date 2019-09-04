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
struct wm831x {int /*<<< orphan*/  io_lock; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,unsigned short,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  wm831x_reg_locked (struct wm831x*,unsigned short) ; 

int wm831x_set_bits(struct wm831x *wm831x, unsigned short reg,
		    unsigned short mask, unsigned short val)
{
	int ret;

	mutex_lock(&wm831x->io_lock);

	if (!wm831x_reg_locked(wm831x, reg))
		ret = regmap_update_bits(wm831x->regmap, reg, mask, val);
	else
		ret = -EPERM;

	mutex_unlock(&wm831x->io_lock);

	return ret;
}