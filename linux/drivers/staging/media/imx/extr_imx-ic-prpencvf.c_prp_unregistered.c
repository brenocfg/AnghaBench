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
struct prp_priv {int /*<<< orphan*/  ctrl_hdlr; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  imx_media_capture_device_unregister (int /*<<< orphan*/ ) ; 
 struct prp_priv* sd_to_priv (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void prp_unregistered(struct v4l2_subdev *sd)
{
	struct prp_priv *priv = sd_to_priv(sd);

	imx_media_capture_device_unregister(priv->vdev);
	v4l2_ctrl_handler_free(&priv->ctrl_hdlr);
}