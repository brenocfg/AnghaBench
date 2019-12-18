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
struct uhid_device {struct uhid_device** outq; } ;
struct inode {int dummy; } ;
struct file {struct uhid_device* private_data; } ;

/* Variables and functions */
 unsigned int UHID_BUFSIZE ; 
 int /*<<< orphan*/  kfree (struct uhid_device*) ; 
 int /*<<< orphan*/  uhid_dev_destroy (struct uhid_device*) ; 

__attribute__((used)) static int uhid_char_release(struct inode *inode, struct file *file)
{
	struct uhid_device *uhid = file->private_data;
	unsigned int i;

	uhid_dev_destroy(uhid);

	for (i = 0; i < UHID_BUFSIZE; ++i)
		kfree(uhid->outq[i]);

	kfree(uhid);

	return 0;
}