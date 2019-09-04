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
struct v4l2_capability {char* bus_info; int device_caps; int capabilities; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct omap_vout_device {TYPE_1__* vfd; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int V4L2_CAP_DEVICE_CAPS ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_OUTPUT ; 
 int V4L2_CAP_VIDEO_OUTPUT_OVERLAY ; 
 int /*<<< orphan*/  VOUT_NAME ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vidioc_querycap(struct file *file, void *fh,
		struct v4l2_capability *cap)
{
	struct omap_vout_device *vout = fh;

	strlcpy(cap->driver, VOUT_NAME, sizeof(cap->driver));
	strlcpy(cap->card, vout->vfd->name, sizeof(cap->card));
	cap->bus_info[0] = '\0';
	cap->device_caps = V4L2_CAP_STREAMING | V4L2_CAP_VIDEO_OUTPUT |
		V4L2_CAP_VIDEO_OUTPUT_OVERLAY;
	cap->capabilities = cap->device_caps | V4L2_CAP_DEVICE_CAPS;

	return 0;
}