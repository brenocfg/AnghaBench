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
struct file {int dummy; } ;
struct camif_vp {int id; TYPE_1__* camif; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  S3C_CAMIF_DRIVER_NAME ; 
 int V4L2_CAP_DEVICE_CAPS ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 char* dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct camif_vp* video_drvdata (struct file*) ; 

__attribute__((used)) static int s3c_camif_vidioc_querycap(struct file *file, void *priv,
				     struct v4l2_capability *cap)
{
	struct camif_vp *vp = video_drvdata(file);

	strlcpy(cap->driver, S3C_CAMIF_DRIVER_NAME, sizeof(cap->driver));
	strlcpy(cap->card, S3C_CAMIF_DRIVER_NAME, sizeof(cap->card));
	snprintf(cap->bus_info, sizeof(cap->bus_info), "platform:%s.%d",
		 dev_name(vp->camif->dev), vp->id);

	cap->device_caps = V4L2_CAP_STREAMING | V4L2_CAP_VIDEO_CAPTURE;
	cap->capabilities = cap->device_caps | V4L2_CAP_DEVICE_CAPS;

	return 0;
}