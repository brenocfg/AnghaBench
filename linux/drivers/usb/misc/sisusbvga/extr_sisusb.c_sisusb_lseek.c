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
struct sisusb_usb_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  sisusb_dev; int /*<<< orphan*/  ready; int /*<<< orphan*/  present; } ;
struct file {struct sisusb_usb_data* private_data; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  no_seek_end_llseek (struct file*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static loff_t sisusb_lseek(struct file *file, loff_t offset, int orig)
{
	struct sisusb_usb_data *sisusb;
	loff_t ret;

	sisusb = file->private_data;
	if (!sisusb)
		return -ENODEV;

	mutex_lock(&sisusb->lock);

	/* Sanity check */
	if (!sisusb->present || !sisusb->ready || !sisusb->sisusb_dev) {
		mutex_unlock(&sisusb->lock);
		return -ENODEV;
	}

	ret = no_seek_end_llseek(file, offset, orig);

	mutex_unlock(&sisusb->lock);
	return ret;
}