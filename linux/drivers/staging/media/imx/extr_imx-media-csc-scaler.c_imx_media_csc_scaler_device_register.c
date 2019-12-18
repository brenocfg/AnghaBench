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
struct video_device {int /*<<< orphan*/  name; int /*<<< orphan*/ * v4l2_dev; } ;
struct ipu_csc_scaler_priv {TYPE_1__* md; } ;
struct imx_media_video_dev {struct video_device* vfd; } ;
struct TYPE_2__ {int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ipu_csc_scaler_priv* vdev_to_priv (struct imx_media_video_dev*) ; 
 int /*<<< orphan*/  video_device_node_name (struct video_device*) ; 
 int video_register_device (struct video_device*,int /*<<< orphan*/ ,int) ; 

int imx_media_csc_scaler_device_register(struct imx_media_video_dev *vdev)
{
	struct ipu_csc_scaler_priv *priv = vdev_to_priv(vdev);
	struct video_device *vfd = vdev->vfd;
	int ret;

	vfd->v4l2_dev = &priv->md->v4l2_dev;

	ret = video_register_device(vfd, VFL_TYPE_GRABBER, -1);
	if (ret) {
		v4l2_err(vfd->v4l2_dev, "Failed to register video device\n");
		return ret;
	}

	v4l2_info(vfd->v4l2_dev, "Registered %s as /dev/%s\n", vfd->name,
		  video_device_node_name(vfd));

	return 0;
}