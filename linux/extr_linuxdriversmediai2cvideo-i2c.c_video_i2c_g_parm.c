#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct video_i2c_data {TYPE_2__* chip; } ;
struct TYPE_5__ {int numerator; int /*<<< orphan*/  denominator; } ;
struct TYPE_8__ {int readbuffers; TYPE_1__ timeperframe; int /*<<< orphan*/  capability; } ;
struct TYPE_7__ {TYPE_4__ capture; } ;
struct v4l2_streamparm {scalar_t__ type; TYPE_3__ parm; } ;
struct file {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  max_fps; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_CAP_TIMEPERFRAME ; 
 struct video_i2c_data* video_drvdata (struct file*) ; 

__attribute__((used)) static int video_i2c_g_parm(struct file *filp, void *priv,
			      struct v4l2_streamparm *parm)
{
	struct video_i2c_data *data = video_drvdata(filp);

	if (parm->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	parm->parm.capture.readbuffers = 1;
	parm->parm.capture.capability = V4L2_CAP_TIMEPERFRAME;
	parm->parm.capture.timeperframe.numerator = 1;
	parm->parm.capture.timeperframe.denominator = data->chip->max_fps;

	return 0;
}