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
struct platform_device {int dummy; } ;
struct imx_media_dev {int /*<<< orphan*/  md; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  m2m_vdev; int /*<<< orphan*/  notifier; } ;

/* Variables and functions */
 int /*<<< orphan*/  imx_media_csc_scaler_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_media_unregister_ipu_internal_subdevs (struct imx_media_dev*) ; 
 int /*<<< orphan*/  media_device_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_device_unregister (int /*<<< orphan*/ *) ; 
 scalar_t__ platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int imx_media_remove(struct platform_device *pdev)
{
	struct imx_media_dev *imxmd =
		(struct imx_media_dev *)platform_get_drvdata(pdev);

	v4l2_info(&imxmd->v4l2_dev, "Removing imx-media\n");

	v4l2_async_notifier_unregister(&imxmd->notifier);
	imx_media_unregister_ipu_internal_subdevs(imxmd);
	v4l2_async_notifier_cleanup(&imxmd->notifier);
	imx_media_csc_scaler_device_unregister(imxmd->m2m_vdev);
	media_device_unregister(&imxmd->md);
	v4l2_device_unregister(&imxmd->v4l2_dev);
	media_device_cleanup(&imxmd->md);

	return 0;
}