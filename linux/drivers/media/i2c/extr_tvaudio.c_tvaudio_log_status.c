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
struct CHIPSTATE {int /*<<< orphan*/  hdl; struct CHIPDESC* desc; } ;
struct CHIPDESC {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct CHIPSTATE* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_log_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_info (struct v4l2_subdev*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tvaudio_log_status(struct v4l2_subdev *sd)
{
	struct CHIPSTATE *chip = to_state(sd);
	struct CHIPDESC *desc = chip->desc;

	v4l2_info(sd, "Chip: %s\n", desc->name);
	v4l2_ctrl_handler_log_status(&chip->hdl, sd->name);
	return 0;
}