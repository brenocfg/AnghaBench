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
struct v4l2_ctrl {void* priv; } ;

/* Variables and functions */

__attribute__((used)) static inline void m5mols_set_ctrl_mode(struct v4l2_ctrl *ctrl,
					unsigned int mode)
{
	ctrl->priv = (void *)(uintptr_t)mode;
}