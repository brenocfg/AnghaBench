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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_ctrl {scalar_t__ is_ptr; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_CTRL_FLAG_HAS_PAYLOAD ; 

__attribute__((used)) static u32 user_flags(const struct v4l2_ctrl *ctrl)
{
	u32 flags = ctrl->flags;

	if (ctrl->is_ptr)
		flags |= V4L2_CTRL_FLAG_HAS_PAYLOAD;

	return flags;
}