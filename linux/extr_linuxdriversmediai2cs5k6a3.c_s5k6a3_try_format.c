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
struct v4l2_mbus_framefmt {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  field; int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int /*<<< orphan*/  S5K6A3_SENSOR_MAX_HEIGHT ; 
 int /*<<< orphan*/  S5K6A3_SENSOR_MAX_WIDTH ; 
 int /*<<< orphan*/  S5K6A3_SENSOR_MIN_HEIGHT ; 
 int /*<<< orphan*/  S5K6A3_SENSOR_MIN_WIDTH ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 struct v4l2_mbus_framefmt* find_sensor_format (struct v4l2_mbus_framefmt*) ; 
 int /*<<< orphan*/  v4l_bound_align_image (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s5k6a3_try_format(struct v4l2_mbus_framefmt *mf)
{
	const struct v4l2_mbus_framefmt *fmt;

	fmt = find_sensor_format(mf);
	mf->code = fmt->code;
	mf->field = V4L2_FIELD_NONE;
	v4l_bound_align_image(&mf->width, S5K6A3_SENSOR_MIN_WIDTH,
			      S5K6A3_SENSOR_MAX_WIDTH, 0,
			      &mf->height, S5K6A3_SENSOR_MIN_HEIGHT,
			      S5K6A3_SENSOR_MAX_HEIGHT, 0, 0);
}