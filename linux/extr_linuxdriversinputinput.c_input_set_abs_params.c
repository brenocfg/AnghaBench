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
struct input_dev {int /*<<< orphan*/  absbit; int /*<<< orphan*/  evbit; struct input_absinfo* absinfo; } ;
struct input_absinfo {int minimum; int maximum; int fuzz; int flat; } ;

/* Variables and functions */
 unsigned int EV_ABS ; 
 int /*<<< orphan*/  __set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_alloc_absinfo (struct input_dev*) ; 

void input_set_abs_params(struct input_dev *dev, unsigned int axis,
			  int min, int max, int fuzz, int flat)
{
	struct input_absinfo *absinfo;

	input_alloc_absinfo(dev);
	if (!dev->absinfo)
		return;

	absinfo = &dev->absinfo[axis];
	absinfo->minimum = min;
	absinfo->maximum = max;
	absinfo->fuzz = fuzz;
	absinfo->flat = flat;

	__set_bit(EV_ABS, dev->evbit);
	__set_bit(axis, dev->absbit);
}