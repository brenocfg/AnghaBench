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
struct v4l2_ctrl {scalar_t__ val; scalar_t__ manual_mode_value; scalar_t__ is_auto; } ;

/* Variables and functions */

__attribute__((used)) static bool is_new_manual(const struct v4l2_ctrl *master)
{
	return master->is_auto && master->val == master->manual_mode_value;
}