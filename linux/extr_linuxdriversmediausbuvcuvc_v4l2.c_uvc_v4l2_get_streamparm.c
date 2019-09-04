#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct TYPE_10__ {void* denominator; void* numerator; } ;
struct TYPE_11__ {TYPE_4__ timeperframe; scalar_t__ outputmode; void* capability; } ;
struct TYPE_8__ {void* denominator; void* numerator; } ;
struct TYPE_9__ {scalar_t__ readbuffers; scalar_t__ extendedmode; TYPE_2__ timeperframe; scalar_t__ capturemode; void* capability; } ;
struct TYPE_12__ {TYPE_5__ output; TYPE_3__ capture; } ;
struct v4l2_streamparm {scalar_t__ type; TYPE_6__ parm; } ;
struct TYPE_7__ {void* dwFrameInterval; } ;
struct uvc_streaming {scalar_t__ type; int /*<<< orphan*/  mutex; TYPE_1__ ctrl; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 void* V4L2_CAP_TIMEPERFRAME ; 
 int /*<<< orphan*/  memset (struct v4l2_streamparm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uvc_simplify_fraction (void**,void**,int,int) ; 

__attribute__((used)) static int uvc_v4l2_get_streamparm(struct uvc_streaming *stream,
		struct v4l2_streamparm *parm)
{
	u32 numerator, denominator;

	if (parm->type != stream->type)
		return -EINVAL;

	mutex_lock(&stream->mutex);
	numerator = stream->ctrl.dwFrameInterval;
	mutex_unlock(&stream->mutex);

	denominator = 10000000;
	uvc_simplify_fraction(&numerator, &denominator, 8, 333);

	memset(parm, 0, sizeof(*parm));
	parm->type = stream->type;

	if (stream->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) {
		parm->parm.capture.capability = V4L2_CAP_TIMEPERFRAME;
		parm->parm.capture.capturemode = 0;
		parm->parm.capture.timeperframe.numerator = numerator;
		parm->parm.capture.timeperframe.denominator = denominator;
		parm->parm.capture.extendedmode = 0;
		parm->parm.capture.readbuffers = 0;
	} else {
		parm->parm.output.capability = V4L2_CAP_TIMEPERFRAME;
		parm->parm.output.outputmode = 0;
		parm->parm.output.timeperframe.numerator = numerator;
		parm->parm.output.timeperframe.denominator = denominator;
	}

	return 0;
}