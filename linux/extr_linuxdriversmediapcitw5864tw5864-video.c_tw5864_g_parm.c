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
struct TYPE_4__ {int /*<<< orphan*/  numerator; } ;
struct v4l2_captureparm {int readbuffers; scalar_t__ capturemode; TYPE_2__ timeperframe; int /*<<< orphan*/  capability; } ;
struct TYPE_3__ {struct v4l2_captureparm capture; } ;
struct v4l2_streamparm {TYPE_1__ parm; } ;
struct tw5864_input {int /*<<< orphan*/  frame_interval; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_CAP_TIMEPERFRAME ; 
 int tw5864_frameinterval_get (struct tw5864_input*,TYPE_2__*) ; 
 struct tw5864_input* video_drvdata (struct file*) ; 

__attribute__((used)) static int tw5864_g_parm(struct file *file, void *priv,
			 struct v4l2_streamparm *sp)
{
	struct tw5864_input *input = video_drvdata(file);
	struct v4l2_captureparm *cp = &sp->parm.capture;
	int ret;

	cp->capability = V4L2_CAP_TIMEPERFRAME;

	ret = tw5864_frameinterval_get(input, &cp->timeperframe);
	cp->timeperframe.numerator *= input->frame_interval;
	cp->capturemode = 0;
	cp->readbuffers = 2;

	return ret;
}