#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int dummy; } ;
struct v4l2_enum_dv_timings {int /*<<< orphan*/  pad; } ;
struct rvin_dev {TYPE_1__* parallel; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sink_pad; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  enum_dv_timings ; 
 int /*<<< orphan*/  pad ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_enum_dv_timings*) ; 
 struct rvin_dev* video_drvdata (struct file*) ; 
 struct v4l2_subdev* vin_to_source (struct rvin_dev*) ; 

__attribute__((used)) static int rvin_enum_dv_timings(struct file *file, void *priv_fh,
				struct v4l2_enum_dv_timings *timings)
{
	struct rvin_dev *vin = video_drvdata(file);
	struct v4l2_subdev *sd = vin_to_source(vin);
	int ret;

	if (timings->pad)
		return -EINVAL;

	timings->pad = vin->parallel->sink_pad;

	ret = v4l2_subdev_call(sd, pad, enum_dv_timings, timings);

	timings->pad = 0;

	return ret;
}