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
struct inode {int dummy; } ;
struct file {struct as102_dev_t* private_data; } ;
struct as102_dev_t {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  as102_usb_release ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int as102_release(struct inode *inode, struct file *file)
{
	struct as102_dev_t *dev = NULL;

	dev = file->private_data;
	if (dev != NULL) {
		/* decrement the count on our device */
		kref_put(&dev->kref, as102_usb_release);
	}

	return 0;
}