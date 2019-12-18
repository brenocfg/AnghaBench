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
struct v4l2_subdev {int /*<<< orphan*/  name; } ;
struct noon010_info {int /*<<< orphan*/  hdl; } ;

/* Variables and functions */
 struct noon010_info* to_noon010 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_log_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int noon010_log_status(struct v4l2_subdev *sd)
{
	struct noon010_info *info = to_noon010(sd);

	v4l2_ctrl_handler_log_status(&info->hdl, sd->name);
	return 0;
}