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
struct v4l2_edid {int /*<<< orphan*/  pad; } ;
struct rvin_dev {TYPE_1__* parallel; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sink_pad; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  get_edid ; 
 int /*<<< orphan*/  pad ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_edid*) ; 
 struct rvin_dev* video_drvdata (struct file*) ; 
 struct v4l2_subdev* vin_to_source (struct rvin_dev*) ; 

__attribute__((used)) static int rvin_g_edid(struct file *file, void *fh, struct v4l2_edid *edid)
{
	struct rvin_dev *vin = video_drvdata(file);
	struct v4l2_subdev *sd = vin_to_source(vin);
	int ret;

	if (edid->pad)
		return -EINVAL;

	edid->pad = vin->parallel->sink_pad;

	ret = v4l2_subdev_call(sd, pad, get_edid, edid);

	edid->pad = 0;

	return ret;
}