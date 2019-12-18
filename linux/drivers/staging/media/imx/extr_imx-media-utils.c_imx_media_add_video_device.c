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
struct imx_media_video_dev {int /*<<< orphan*/  list; } ;
struct imx_media_dev {int /*<<< orphan*/  mutex; int /*<<< orphan*/  vdev_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void imx_media_add_video_device(struct imx_media_dev *imxmd,
				struct imx_media_video_dev *vdev)
{
	mutex_lock(&imxmd->mutex);

	list_add_tail(&vdev->list, &imxmd->vdev_list);

	mutex_unlock(&imxmd->mutex);
}