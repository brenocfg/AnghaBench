#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_10__ {int error; } ;
struct TYPE_9__ {TYPE_4__* ctrl_handler; } ;
struct et8ek8_sensor {TYPE_4__ ctrl_handler; TYPE_3__ subdev; void* pixel_rate; void* exposure; TYPE_2__* current_reglist; } ;
typedef  int s32 ;
struct TYPE_7__ {int max_exp; } ;
struct TYPE_8__ {TYPE_1__ mode; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int INT_MAX ; 
 int /*<<< orphan*/  V4L2_CID_EXPOSURE ; 
 int /*<<< orphan*/  V4L2_CID_GAIN ; 
 int /*<<< orphan*/  V4L2_CID_PIXEL_RATE ; 
 int /*<<< orphan*/  V4L2_CID_TEST_PATTERN ; 
 int /*<<< orphan*/  et8ek8_ctrl_ops ; 
 int /*<<< orphan*/  et8ek8_gain_table ; 
 int /*<<< orphan*/  et8ek8_test_pattern_menu ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_4__*,int) ; 
 void* v4l2_ctrl_new_std (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std_menu_items (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int et8ek8_init_controls(struct et8ek8_sensor *sensor)
{
	s32 max_rows;

	v4l2_ctrl_handler_init(&sensor->ctrl_handler, 4);

	/* V4L2_CID_GAIN */
	v4l2_ctrl_new_std(&sensor->ctrl_handler, &et8ek8_ctrl_ops,
			  V4L2_CID_GAIN, 0, ARRAY_SIZE(et8ek8_gain_table) - 1,
			  1, 0);

	max_rows = sensor->current_reglist->mode.max_exp;
	{
		u32 min = 1, max = max_rows;

		sensor->exposure =
			v4l2_ctrl_new_std(&sensor->ctrl_handler,
					  &et8ek8_ctrl_ops, V4L2_CID_EXPOSURE,
					  min, max, min, max);
	}

	/* V4L2_CID_PIXEL_RATE */
	sensor->pixel_rate =
		v4l2_ctrl_new_std(&sensor->ctrl_handler, &et8ek8_ctrl_ops,
		V4L2_CID_PIXEL_RATE, 1, INT_MAX, 1, 1);

	/* V4L2_CID_TEST_PATTERN */
	v4l2_ctrl_new_std_menu_items(&sensor->ctrl_handler,
				     &et8ek8_ctrl_ops, V4L2_CID_TEST_PATTERN,
				     ARRAY_SIZE(et8ek8_test_pattern_menu) - 1,
				     0, 0, et8ek8_test_pattern_menu);

	if (sensor->ctrl_handler.error)
		return sensor->ctrl_handler.error;

	sensor->subdev.ctrl_handler = &sensor->ctrl_handler;

	return 0;
}