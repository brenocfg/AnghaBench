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
struct imx_media_video_dev {int dummy; } ;
struct capture_priv {int /*<<< orphan*/  ctrl_hdlr; } ;

/* Variables and functions */
 struct capture_priv* to_capture_priv (struct imx_media_video_dev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 

void imx_media_capture_device_remove(struct imx_media_video_dev *vdev)
{
	struct capture_priv *priv = to_capture_priv(vdev);

	v4l2_ctrl_handler_free(&priv->ctrl_hdlr);
}