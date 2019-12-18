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

/* Variables and functions */
 unsigned int NVME_IOCTL_ADMIN64_CMD ; 
 unsigned int NVME_IOCTL_ADMIN_CMD ; 
 scalar_t__ is_sed_ioctl (unsigned int) ; 

__attribute__((used)) static bool is_ctrl_ioctl(unsigned int cmd)
{
	if (cmd == NVME_IOCTL_ADMIN_CMD || cmd == NVME_IOCTL_ADMIN64_CMD)
		return true;
	if (is_sed_ioctl(cmd))
		return true;
	return false;
}