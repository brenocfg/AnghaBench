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
struct v4l2_subdev {int /*<<< orphan*/  name; int /*<<< orphan*/  ctrl_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  v4l2_ctrl_handler_log_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5k6aa_log_status(struct v4l2_subdev *sd)
{
	v4l2_ctrl_handler_log_status(sd->ctrl_handler, sd->name);
	return 0;
}