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
struct v4l2_subdev {int /*<<< orphan*/  entity; } ;
struct platform_device {int dummy; } ;
struct csi_priv {int /*<<< orphan*/  vdev; int /*<<< orphan*/  lock; int /*<<< orphan*/  ctrl_hdlr; } ;

/* Variables and functions */
 int /*<<< orphan*/  imx_media_capture_device_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct v4l2_subdev* platform_get_drvdata (struct platform_device*) ; 
 struct csi_priv* sd_to_dev (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_async_unregister_subdev (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int imx_csi_remove(struct platform_device *pdev)
{
	struct v4l2_subdev *sd = platform_get_drvdata(pdev);
	struct csi_priv *priv = sd_to_dev(sd);

	v4l2_ctrl_handler_free(&priv->ctrl_hdlr);
	mutex_destroy(&priv->lock);
	imx_media_capture_device_remove(priv->vdev);
	v4l2_async_unregister_subdev(sd);
	media_entity_cleanup(&sd->entity);

	return 0;
}