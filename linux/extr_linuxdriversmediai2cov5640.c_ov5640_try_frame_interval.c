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
typedef  int u32 ;
struct v4l2_fract {int numerator; int denominator; } ;
struct ov5640_mode_info {int dummy; } ;
struct ov5640_dev {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int) ; 
 int EINVAL ; 
 size_t OV5640_15_FPS ; 
 size_t OV5640_30_FPS ; 
 struct ov5640_mode_info* ov5640_find_mode (struct ov5640_dev*,int,int,int,int) ; 
 int* ov5640_framerates ; 

__attribute__((used)) static int ov5640_try_frame_interval(struct ov5640_dev *sensor,
				     struct v4l2_fract *fi,
				     u32 width, u32 height)
{
	const struct ov5640_mode_info *mode;
	u32 minfps, maxfps, fps;
	int ret;

	minfps = ov5640_framerates[OV5640_15_FPS];
	maxfps = ov5640_framerates[OV5640_30_FPS];

	if (fi->numerator == 0) {
		fi->denominator = maxfps;
		fi->numerator = 1;
		return OV5640_30_FPS;
	}

	fps = DIV_ROUND_CLOSEST(fi->denominator, fi->numerator);

	fi->numerator = 1;
	if (fps > maxfps)
		fi->denominator = maxfps;
	else if (fps < minfps)
		fi->denominator = minfps;
	else if (2 * fps >= 2 * minfps + (maxfps - minfps))
		fi->denominator = maxfps;
	else
		fi->denominator = minfps;

	ret = (fi->denominator == minfps) ? OV5640_15_FPS : OV5640_30_FPS;

	mode = ov5640_find_mode(sensor, ret, width, height, false);
	return mode ? ret : -EINVAL;
}