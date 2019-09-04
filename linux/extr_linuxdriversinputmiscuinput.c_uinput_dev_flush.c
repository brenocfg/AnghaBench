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
struct input_dev {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int input_ff_flush (struct input_dev*,struct file*) ; 

__attribute__((used)) static int uinput_dev_flush(struct input_dev *dev, struct file *file)
{
	/*
	 * If we are called with file == NULL that means we are tearing
	 * down the device, and therefore we can not handle FF erase
	 * requests: either we are handling UI_DEV_DESTROY (and holding
	 * the udev->mutex), or the file descriptor is closed and there is
	 * nobody on the other side anymore.
	 */
	return file ? input_ff_flush(dev, file) : 0;
}