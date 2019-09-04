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
struct rc_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  input_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  input_free_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

void rc_free_device(struct rc_dev *dev)
{
	if (!dev)
		return;

	input_free_device(dev->input_dev);

	put_device(&dev->dev);

	/* kfree(dev) will be called by the callback function
	   rc_dev_release() */

	module_put(THIS_MODULE);
}