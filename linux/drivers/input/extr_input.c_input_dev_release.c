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
struct input_dev {struct input_dev* vals; struct input_dev* absinfo; struct input_dev* poller; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  input_ff_destroy (struct input_dev*) ; 
 int /*<<< orphan*/  input_mt_destroy_slots (struct input_dev*) ; 
 int /*<<< orphan*/  kfree (struct input_dev*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 struct input_dev* to_input_dev (struct device*) ; 

__attribute__((used)) static void input_dev_release(struct device *device)
{
	struct input_dev *dev = to_input_dev(device);

	input_ff_destroy(dev);
	input_mt_destroy_slots(dev);
	kfree(dev->poller);
	kfree(dev->absinfo);
	kfree(dev->vals);
	kfree(dev);

	module_put(THIS_MODULE);
}