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
struct timer_list {int dummy; } ;
struct prp_priv {struct imx_ic_priv* ic_priv; struct imx_media_video_dev* vdev; } ;
struct imx_media_video_dev {int dummy; } ;
struct imx_ic_priv {int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  eof_timeout_timer ; 
 struct prp_priv* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_media_capture_device_error (struct imx_media_video_dev*) ; 
 struct prp_priv* priv ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void prp_eof_timeout(struct timer_list *t)
{
	struct prp_priv *priv = from_timer(priv, t, eof_timeout_timer);
	struct imx_media_video_dev *vdev = priv->vdev;
	struct imx_ic_priv *ic_priv = priv->ic_priv;

	v4l2_err(&ic_priv->sd, "EOF timeout\n");

	/* signal a fatal error to capture device */
	imx_media_capture_device_error(vdev);
}