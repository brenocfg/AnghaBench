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
 int EINVAL ; 
 int ENOIOCTLCMD ; 
 int ENOTTY ; 

__attribute__((used)) static inline int is_unrecognized_ioctl(int ret)
{
	return	ret == -EINVAL ||
		ret == -ENOTTY ||
		ret == -ENOIOCTLCMD;
}