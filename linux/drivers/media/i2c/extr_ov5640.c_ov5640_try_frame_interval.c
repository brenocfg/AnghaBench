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
struct v4l2_fract {int numerator; int denominator; } ;
struct ov5640_mode_info {int dummy; } ;
struct ov5640_dev {int dummy; } ;
typedef  enum ov5640_frame_rate { ____Placeholder_ov5640_frame_rate } ov5640_frame_rate ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  DIV_ROUND_CLOSEST (int,int) ; 
 int EINVAL ; 
 size_t OV5640_15_FPS ; 
 size_t OV5640_60_FPS ; 
 scalar_t__ abs (int) ; 
 int clamp_val (int /*<<< orphan*/ ,int,int) ; 
 struct ov5640_mode_info* ov5640_find_mode (struct ov5640_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int* ov5640_framerates ; 

__attribute__((used)) static int ov5640_try_frame_interval(struct ov5640_dev *sensor,
				     struct v4l2_fract *fi,
				     u32 width, u32 height)
{
	const struct ov5640_mode_info *mode;
	enum ov5640_frame_rate rate = OV5640_15_FPS;
	int minfps, maxfps, best_fps, fps;
	int i;

	minfps = ov5640_framerates[OV5640_15_FPS];
	maxfps = ov5640_framerates[OV5640_60_FPS];

	if (fi->numerator == 0) {
		fi->denominator = maxfps;
		fi->numerator = 1;
		rate = OV5640_60_FPS;
		goto find_mode;
	}

	fps = clamp_val(DIV_ROUND_CLOSEST(fi->denominator, fi->numerator),
			minfps, maxfps);

	best_fps = minfps;
	for (i = 0; i < ARRAY_SIZE(ov5640_framerates); i++) {
		int curr_fps = ov5640_framerates[i];

		if (abs(curr_fps - fps) < abs(best_fps - fps)) {
			best_fps = curr_fps;
			rate = i;
		}
	}

	fi->numerator = 1;
	fi->denominator = best_fps;

find_mode:
	mode = ov5640_find_mode(sensor, rate, width, height, false);
	return mode ? rate : -EINVAL;
}