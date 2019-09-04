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
struct input_dev {struct ff_device* ff; int /*<<< orphan*/  evbit; } ;
struct ff_device {struct ff_device* effects; struct ff_device* private; int /*<<< orphan*/  (* destroy ) (struct ff_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EV_FF ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ff_device*) ; 
 int /*<<< orphan*/  stub1 (struct ff_device*) ; 

void input_ff_destroy(struct input_dev *dev)
{
	struct ff_device *ff = dev->ff;

	__clear_bit(EV_FF, dev->evbit);
	if (ff) {
		if (ff->destroy)
			ff->destroy(ff);
		kfree(ff->private);
		kfree(ff->effects);
		kfree(ff);
		dev->ff = NULL;
	}
}