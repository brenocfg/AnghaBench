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
struct file {int dummy; } ;

/* Variables and functions */
 long EINVAL ; 
#define  IOCTL_MBOX_PROPERTY 128 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 
 long vcio_user_property_list (void*) ; 

__attribute__((used)) static long vcio_device_ioctl(struct file *file, unsigned int ioctl_num,
			      unsigned long ioctl_param)
{
	switch (ioctl_num) {
	case IOCTL_MBOX_PROPERTY:
		return vcio_user_property_list((void *)ioctl_param);
	default:
		pr_err("unknown ioctl: %x\n", ioctl_num);
		return -EINVAL;
	}
}