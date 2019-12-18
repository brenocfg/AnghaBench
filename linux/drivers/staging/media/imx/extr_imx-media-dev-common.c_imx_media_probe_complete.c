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
struct v4l2_async_notifier {int dummy; } ;
struct imx_media_dev {int /*<<< orphan*/  md; int /*<<< orphan*/  mutex; int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int imx_media_create_links (struct v4l2_async_notifier*) ; 
 int imx_media_create_pad_vdev_lists (struct imx_media_dev*) ; 
 int media_device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct imx_media_dev* notifier2dev (struct v4l2_async_notifier*) ; 
 int v4l2_device_register_subdev_nodes (int /*<<< orphan*/ *) ; 

int imx_media_probe_complete(struct v4l2_async_notifier *notifier)
{
	struct imx_media_dev *imxmd = notifier2dev(notifier);
	int ret;

	mutex_lock(&imxmd->mutex);

	ret = imx_media_create_links(notifier);
	if (ret)
		goto unlock;

	ret = imx_media_create_pad_vdev_lists(imxmd);
	if (ret)
		goto unlock;

	ret = v4l2_device_register_subdev_nodes(&imxmd->v4l2_dev);
unlock:
	mutex_unlock(&imxmd->mutex);
	if (ret)
		return ret;

	return media_device_register(&imxmd->md);
}