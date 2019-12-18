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
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_ACTIVE ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_TRY ; 

__attribute__((used)) static inline int check_which(__u32 which)
{
	if (which != V4L2_SUBDEV_FORMAT_TRY &&
	    which != V4L2_SUBDEV_FORMAT_ACTIVE)
		return -EINVAL;

	return 0;
}