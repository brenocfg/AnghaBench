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
typedef  scalar_t__ u32 ;
struct v4l2_ext_control {scalar_t__ id; } ;

/* Variables and functions */

__attribute__((used)) static bool uvc_ctrl_xctrls_has_control(const struct v4l2_ext_control *xctrls,
					unsigned int xctrls_count, u32 id)
{
	unsigned int i;

	for (i = 0; i < xctrls_count; ++i) {
		if (xctrls[i].id == id)
			return true;
	}

	return false;
}