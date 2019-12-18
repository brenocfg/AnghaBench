#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct video_device {int /*<<< orphan*/ * lock; } ;
struct imx_media_video_dev {int /*<<< orphan*/  list; struct video_device* vfd; } ;
struct ipu_csc_scaler_priv {struct imx_media_video_dev vdev; int /*<<< orphan*/  m2m_dev; int /*<<< orphan*/  mutex; int /*<<< orphan*/  dev; struct imx_media_dev* md; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct imx_media_dev {int /*<<< orphan*/  v4l2_dev; TYPE_1__ md; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct imx_media_video_dev* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct video_device ipu_csc_scaler_videodev_template ; 
 int /*<<< orphan*/  kfree (struct ipu_csc_scaler_priv*) ; 
 struct ipu_csc_scaler_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m2m_ops ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  v4l2_m2m_init (int /*<<< orphan*/ *) ; 
 struct video_device* video_device_alloc () ; 
 int /*<<< orphan*/  video_set_drvdata (struct video_device*,struct ipu_csc_scaler_priv*) ; 

struct imx_media_video_dev *
imx_media_csc_scaler_device_init(struct imx_media_dev *md)
{
	struct ipu_csc_scaler_priv *priv;
	struct video_device *vfd;
	int ret;

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return ERR_PTR(-ENOMEM);

	priv->md = md;
	priv->dev = md->md.dev;

	mutex_init(&priv->mutex);

	vfd = video_device_alloc();
	if (!vfd) {
		ret = -ENOMEM;
		goto err_vfd;
	}

	*vfd = ipu_csc_scaler_videodev_template;
	vfd->lock = &priv->mutex;
	priv->vdev.vfd = vfd;

	INIT_LIST_HEAD(&priv->vdev.list);

	video_set_drvdata(vfd, priv);

	priv->m2m_dev = v4l2_m2m_init(&m2m_ops);
	if (IS_ERR(priv->m2m_dev)) {
		ret = PTR_ERR(priv->m2m_dev);
		v4l2_err(&md->v4l2_dev, "Failed to init mem2mem device: %d\n",
			 ret);
		goto err_m2m;
	}

	return &priv->vdev;

err_m2m:
	video_set_drvdata(vfd, NULL);
err_vfd:
	kfree(priv);
	return ERR_PTR(ret);
}