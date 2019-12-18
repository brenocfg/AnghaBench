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
struct video_device {int dummy; } ;
struct TYPE_2__ {struct video_device* vfd; } ;
struct ipu_csc_scaler_priv {int /*<<< orphan*/  mutex; TYPE_1__ vdev; } ;
struct imx_media_video_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ipu_csc_scaler_priv* vdev_to_priv (struct imx_media_video_dev*) ; 
 int /*<<< orphan*/  video_unregister_device (struct video_device*) ; 

void imx_media_csc_scaler_device_unregister(struct imx_media_video_dev *vdev)
{
	struct ipu_csc_scaler_priv *priv = vdev_to_priv(vdev);
	struct video_device *vfd = priv->vdev.vfd;

	mutex_lock(&priv->mutex);

	video_unregister_device(vfd);

	mutex_unlock(&priv->mutex);
}