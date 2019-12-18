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
struct imx_media_dev {int /*<<< orphan*/  mutex; int /*<<< orphan*/  m2m_vdev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_media_csc_scaler_device_init (struct imx_media_dev*) ; 
 int imx_media_csc_scaler_device_register (int /*<<< orphan*/ ) ; 
 int imx_media_probe_complete (struct v4l2_async_notifier*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct imx_media_dev* notifier2dev (struct v4l2_async_notifier*) ; 

__attribute__((used)) static int imx6_media_probe_complete(struct v4l2_async_notifier *notifier)
{
	struct imx_media_dev *imxmd = notifier2dev(notifier);
	int ret;

	/* call the imx5/6/7 common probe completion handler */
	ret = imx_media_probe_complete(notifier);
	if (ret)
		return ret;

	mutex_lock(&imxmd->mutex);

	imxmd->m2m_vdev = imx_media_csc_scaler_device_init(imxmd);
	if (IS_ERR(imxmd->m2m_vdev)) {
		ret = PTR_ERR(imxmd->m2m_vdev);
		goto unlock;
	}

	ret = imx_media_csc_scaler_device_register(imxmd->m2m_vdev);
unlock:
	mutex_unlock(&imxmd->mutex);
	return ret;
}