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
struct v4l2_capability {int device_caps; int capabilities; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; int /*<<< orphan*/  bus_info; } ;
struct file {int dummy; } ;

/* Variables and functions */
 char* PXA_CAM_DRV_NAME ; 
 int V4L2_CAP_DEVICE_CAPS ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 char* pxa_cam_driver_description ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int pxac_vidioc_querycap(struct file *file, void *priv,
				struct v4l2_capability *cap)
{
	strlcpy(cap->bus_info, "platform:pxa-camera", sizeof(cap->bus_info));
	strlcpy(cap->driver, PXA_CAM_DRV_NAME, sizeof(cap->driver));
	strlcpy(cap->card, pxa_cam_driver_description, sizeof(cap->card));
	cap->device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING;
	cap->capabilities = cap->device_caps | V4L2_CAP_DEVICE_CAPS;

	return 0;
}