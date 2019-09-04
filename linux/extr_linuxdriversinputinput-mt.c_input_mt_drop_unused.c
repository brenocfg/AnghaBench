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
struct input_mt {int /*<<< orphan*/  frame; } ;
struct input_dev {struct input_mt* mt; } ;

/* Variables and functions */
 int /*<<< orphan*/  __input_mt_drop_unused (struct input_dev*,struct input_mt*) ; 

void input_mt_drop_unused(struct input_dev *dev)
{
	struct input_mt *mt = dev->mt;

	if (mt) {
		__input_mt_drop_unused(dev, mt);
		mt->frame++;
	}
}