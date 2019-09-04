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
struct sync_timeline {int dummy; } ;
struct file {struct sync_timeline* private_data; } ;

/* Variables and functions */
 long ENOTTY ; 
#define  SW_SYNC_IOC_CREATE_FENCE 129 
#define  SW_SYNC_IOC_INC 128 
 long sw_sync_ioctl_create_fence (struct sync_timeline*,unsigned long) ; 
 long sw_sync_ioctl_inc (struct sync_timeline*,unsigned long) ; 

__attribute__((used)) static long sw_sync_ioctl(struct file *file, unsigned int cmd,
			  unsigned long arg)
{
	struct sync_timeline *obj = file->private_data;

	switch (cmd) {
	case SW_SYNC_IOC_CREATE_FENCE:
		return sw_sync_ioctl_create_fence(obj, arg);

	case SW_SYNC_IOC_INC:
		return sw_sync_ioctl_inc(obj, arg);

	default:
		return -ENOTTY;
	}
}