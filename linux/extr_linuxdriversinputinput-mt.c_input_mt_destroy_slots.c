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
struct input_dev {TYPE_1__* mt; } ;
struct TYPE_2__ {struct TYPE_2__* red; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

void input_mt_destroy_slots(struct input_dev *dev)
{
	if (dev->mt) {
		kfree(dev->mt->red);
		kfree(dev->mt);
	}
	dev->mt = NULL;
}