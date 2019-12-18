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
struct video_device {int /*<<< orphan*/  entity; } ;
struct imx_media_video_dev {int dummy; } ;
struct TYPE_2__ {struct video_device* vfd; } ;
struct capture_priv {int /*<<< orphan*/  mutex; TYPE_1__ vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct capture_priv* to_capture_priv (struct imx_media_video_dev*) ; 
 scalar_t__ video_is_registered (struct video_device*) ; 
 int /*<<< orphan*/  video_unregister_device (struct video_device*) ; 

void imx_media_capture_device_unregister(struct imx_media_video_dev *vdev)
{
	struct capture_priv *priv = to_capture_priv(vdev);
	struct video_device *vfd = priv->vdev.vfd;

	mutex_lock(&priv->mutex);

	if (video_is_registered(vfd)) {
		video_unregister_device(vfd);
		media_entity_cleanup(&vfd->entity);
	}

	mutex_unlock(&priv->mutex);
}