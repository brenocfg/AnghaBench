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
struct file {struct dvb_device* private_data; } ;
struct dvb_device {int /*<<< orphan*/  kernel_ioctl; } ;

/* Variables and functions */
 long EINVAL ; 
 long ENODEV ; 
 long dvb_usercopy (struct file*,unsigned int,unsigned long,int /*<<< orphan*/ ) ; 

long dvb_generic_ioctl(struct file *file,
		       unsigned int cmd, unsigned long arg)
{
	struct dvb_device *dvbdev = file->private_data;

	if (!dvbdev)
		return -ENODEV;

	if (!dvbdev->kernel_ioctl)
		return -EINVAL;

	return dvb_usercopy(file, cmd, arg, dvbdev->kernel_ioctl);
}