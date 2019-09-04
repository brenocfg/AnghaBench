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
struct TYPE_5__ {int readbuffers; TYPE_1__ timeperframe; } ;
struct TYPE_6__ {TYPE_2__ capture; } ;
struct v4l2_streamparm {scalar_t__ type; TYPE_3__ parm; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 

__attribute__((used)) static int cobalt_g_parm(struct file *file, void *fh, struct v4l2_streamparm *a)
{
	if (a->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;
	a->parm.capture.timeperframe.numerator = 1;
	a->parm.capture.timeperframe.denominator = 60;
	a->parm.capture.readbuffers = 3;
	return 0;
}