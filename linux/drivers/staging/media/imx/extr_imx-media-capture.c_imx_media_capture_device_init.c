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
struct video_device {int /*<<< orphan*/ * queue; int /*<<< orphan*/ * lock; int /*<<< orphan*/  name; } ;
struct v4l2_subdev {char* name; } ;
struct imx_media_video_dev {int /*<<< orphan*/  list; struct video_device* vfd; } ;
struct device {int dummy; } ;
struct capture_priv {int src_sd_pad; struct imx_media_video_dev vdev; int /*<<< orphan*/  ctrl_hdlr; int /*<<< orphan*/  q; int /*<<< orphan*/  mutex; int /*<<< orphan*/  q_lock; struct device* dev; struct v4l2_subdev* src_sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct imx_media_video_dev* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct video_device capture_videodev ; 
 struct capture_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct video_device* video_device_alloc () ; 
 int /*<<< orphan*/  video_set_drvdata (struct video_device*,struct capture_priv*) ; 

struct imx_media_video_dev *
imx_media_capture_device_init(struct device *dev, struct v4l2_subdev *src_sd,
			      int pad)
{
	struct capture_priv *priv;
	struct video_device *vfd;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return ERR_PTR(-ENOMEM);

	priv->src_sd = src_sd;
	priv->src_sd_pad = pad;
	priv->dev = dev;

	mutex_init(&priv->mutex);
	spin_lock_init(&priv->q_lock);

	snprintf(capture_videodev.name, sizeof(capture_videodev.name),
		 "%s capture", src_sd->name);

	vfd = video_device_alloc();
	if (!vfd)
		return ERR_PTR(-ENOMEM);

	*vfd = capture_videodev;
	vfd->lock = &priv->mutex;
	vfd->queue = &priv->q;
	priv->vdev.vfd = vfd;

	INIT_LIST_HEAD(&priv->vdev.list);

	video_set_drvdata(vfd, priv);

	v4l2_ctrl_handler_init(&priv->ctrl_hdlr, 0);

	return &priv->vdev;
}