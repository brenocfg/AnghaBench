#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct v4l2_capability {int device_caps; int capabilities; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEM2MEM_NAME ; 
 int V4L2_CAP_DEVICE_CAPS ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 int V4L2_CAP_VIDEO_M2M ; 
 int V4L2_CAP_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vidioc_querycap(struct file *file, void *priv,
			   struct v4l2_capability *cap)
{
	strlcpy(cap->driver, MEM2MEM_NAME, sizeof(cap->driver));
	strlcpy(cap->card, MEM2MEM_NAME, sizeof(cap->card));
	strlcpy(cap->bus_info, MEM2MEM_NAME, sizeof(cap->card));
	/*
	 * This is only a mem-to-mem video device. The capture and output
	 * device capability flags are left only for backward compatibility
	 * and are scheduled for removal.
	 */
	cap->device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_VIDEO_OUTPUT |
			   V4L2_CAP_VIDEO_M2M | V4L2_CAP_STREAMING;
	cap->capabilities = cap->device_caps | V4L2_CAP_DEVICE_CAPS;

	return 0;
}