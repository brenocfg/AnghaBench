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
struct vivid_dev {int /*<<< orphan*/  timeperframe_vid_cap; scalar_t__ multiplanar; } ;
struct TYPE_4__ {int readbuffers; int /*<<< orphan*/  timeperframe; int /*<<< orphan*/  capability; } ;
struct TYPE_3__ {TYPE_2__ capture; } ;
struct v4l2_streamparm {scalar_t__ type; TYPE_1__ parm; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 int /*<<< orphan*/  V4L2_CAP_TIMEPERFRAME ; 
 struct vivid_dev* video_drvdata (struct file*) ; 

int vivid_vid_cap_g_parm(struct file *file, void *priv,
			  struct v4l2_streamparm *parm)
{
	struct vivid_dev *dev = video_drvdata(file);

	if (parm->type != (dev->multiplanar ?
			   V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE :
			   V4L2_BUF_TYPE_VIDEO_CAPTURE))
		return -EINVAL;

	parm->parm.capture.capability   = V4L2_CAP_TIMEPERFRAME;
	parm->parm.capture.timeperframe = dev->timeperframe_vid_cap;
	parm->parm.capture.readbuffers  = 1;
	return 0;
}