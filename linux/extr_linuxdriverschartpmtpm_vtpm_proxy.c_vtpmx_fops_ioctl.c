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
 long ENOIOCTLCMD ; 
#define  VTPM_PROXY_IOC_NEW_DEV 128 
 long vtpmx_ioc_new_dev (struct file*,unsigned int,unsigned long) ; 

__attribute__((used)) static long vtpmx_fops_ioctl(struct file *f, unsigned int ioctl,
			     unsigned long arg)
{
	switch (ioctl) {
	case VTPM_PROXY_IOC_NEW_DEV:
		return vtpmx_ioc_new_dev(f, ioctl, arg);
	default:
		return -ENOIOCTLCMD;
	}
}