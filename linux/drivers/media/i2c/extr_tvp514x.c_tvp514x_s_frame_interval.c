#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_fract {int dummy; } ;
struct v4l2_subdev_frame_interval {struct v4l2_fract interval; } ;
struct v4l2_subdev {int dummy; } ;
struct tvp514x_decoder {int current_std; TYPE_2__* std_list; } ;
typedef  enum tvp514x_std { ____Placeholder_tvp514x_std } tvp514x_std ;
struct TYPE_3__ {struct v4l2_fract frameperiod; } ;
struct TYPE_4__ {TYPE_1__ standard; } ;

/* Variables and functions */
 struct tvp514x_decoder* to_decoder (struct v4l2_subdev*) ; 

__attribute__((used)) static int
tvp514x_s_frame_interval(struct v4l2_subdev *sd,
			 struct v4l2_subdev_frame_interval *ival)
{
	struct tvp514x_decoder *decoder = to_decoder(sd);
	struct v4l2_fract *timeperframe;
	enum tvp514x_std current_std;


	timeperframe = &ival->interval;

	/* get the current standard */
	current_std = decoder->current_std;

	*timeperframe =
	    decoder->std_list[current_std].standard.frameperiod;

	return 0;
}