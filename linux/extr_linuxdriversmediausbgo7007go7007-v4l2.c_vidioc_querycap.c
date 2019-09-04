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
struct v4l2_capability {int device_caps; int capabilities; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct go7007 {char* name; char* bus_info; TYPE_1__* board_info; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int flags; scalar_t__ num_aud_inputs; } ;

/* Variables and functions */
 int GO7007_BOARD_HAS_TUNER ; 
 int V4L2_CAP_AUDIO ; 
 int V4L2_CAP_DEVICE_CAPS ; 
 int V4L2_CAP_READWRITE ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_TUNER ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 struct go7007* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_querycap(struct file *file, void  *priv,
					struct v4l2_capability *cap)
{
	struct go7007 *go = video_drvdata(file);

	strlcpy(cap->driver, "go7007", sizeof(cap->driver));
	strlcpy(cap->card, go->name, sizeof(cap->card));
	strlcpy(cap->bus_info, go->bus_info, sizeof(cap->bus_info));

	cap->device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_READWRITE |
				V4L2_CAP_STREAMING;

	if (go->board_info->num_aud_inputs)
		cap->device_caps |= V4L2_CAP_AUDIO;
	if (go->board_info->flags & GO7007_BOARD_HAS_TUNER)
		cap->device_caps |= V4L2_CAP_TUNER;
	cap->capabilities = cap->device_caps | V4L2_CAP_DEVICE_CAPS;
	return 0;
}