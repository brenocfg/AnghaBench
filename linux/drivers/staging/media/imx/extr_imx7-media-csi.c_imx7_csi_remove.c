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
struct v4l2_subdev {int dummy; } ;
struct platform_device {int dummy; } ;
struct imx_media_dev {int /*<<< orphan*/  md; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  notifier; } ;
struct imx7_csi {int /*<<< orphan*/  lock; int /*<<< orphan*/  ctrl_hdlr; int /*<<< orphan*/  vdev; struct imx_media_dev* imxmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  imx_media_capture_device_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_media_capture_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_device_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct v4l2_subdev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_unregister_subdev (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 struct imx7_csi* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int imx7_csi_remove(struct platform_device *pdev)
{
	struct v4l2_subdev *sd = platform_get_drvdata(pdev);
	struct imx7_csi *csi = v4l2_get_subdevdata(sd);
	struct imx_media_dev *imxmd = csi->imxmd;

	v4l2_async_notifier_unregister(&imxmd->notifier);
	v4l2_async_notifier_cleanup(&imxmd->notifier);

	media_device_unregister(&imxmd->md);
	v4l2_device_unregister(&imxmd->v4l2_dev);
	media_device_cleanup(&imxmd->md);

	imx_media_capture_device_unregister(csi->vdev);
	imx_media_capture_device_remove(csi->vdev);

	v4l2_async_unregister_subdev(sd);
	v4l2_ctrl_handler_free(&csi->ctrl_hdlr);

	mutex_destroy(&csi->lock);

	return 0;
}