#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int numerator; int denominator; } ;
struct TYPE_6__ {int readbuffers; TYPE_1__ timeperframe; int /*<<< orphan*/  capability; } ;
struct TYPE_5__ {TYPE_3__ capture; } ;
struct v4l2_streamparm {scalar_t__ type; TYPE_2__ parm; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_CAP_TIMEPERFRAME ; 

__attribute__((used)) static int sur40_ioctl_parm(struct file *file, void *priv,
			    struct v4l2_streamparm *p)
{
	if (p->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	p->parm.capture.capability = V4L2_CAP_TIMEPERFRAME;
	p->parm.capture.timeperframe.numerator = 1;
	p->parm.capture.timeperframe.denominator = 60;
	p->parm.capture.readbuffers = 3;
	return 0;
}