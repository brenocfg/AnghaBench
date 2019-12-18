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
struct v4l2_capability {int capabilities; int /*<<< orphan*/  card; } ;
struct file {int dummy; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct TYPE_4__ {scalar_t__ tuner_type; TYPE_1__ radio; int /*<<< orphan*/  name; } ;
struct cx88_core {TYPE_2__ board; } ;

/* Variables and functions */
 scalar_t__ CX88_RADIO ; 
 scalar_t__ UNSET ; 
 int V4L2_CAP_DEVICE_CAPS ; 
 int V4L2_CAP_RADIO ; 
 int V4L2_CAP_READWRITE ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_TUNER ; 
 int V4L2_CAP_VBI_CAPTURE ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int cx88_querycap(struct file *file, struct cx88_core *core,
		  struct v4l2_capability *cap)
{
	strscpy(cap->card, core->board.name, sizeof(cap->card));
	cap->capabilities = V4L2_CAP_READWRITE | V4L2_CAP_STREAMING |
			    V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_VBI_CAPTURE |
			    V4L2_CAP_DEVICE_CAPS;
	if (core->board.tuner_type != UNSET)
		cap->capabilities |= V4L2_CAP_TUNER;
	if (core->board.radio.type == CX88_RADIO)
		cap->capabilities |= V4L2_CAP_RADIO;
	return 0;
}