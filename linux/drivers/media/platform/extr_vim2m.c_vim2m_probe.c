#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_5__* mdev; } ;
struct video_device {int /*<<< orphan*/  num; TYPE_1__* v4l2_dev; int /*<<< orphan*/ * lock; } ;
struct TYPE_8__ {int /*<<< orphan*/ * ops; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  model; int /*<<< orphan*/ * dev; } ;
struct vim2m_dev {TYPE_1__ v4l2_dev; struct video_device vfd; int /*<<< orphan*/  m2m_dev; TYPE_5__ mdev; int /*<<< orphan*/  dev_mutex; int /*<<< orphan*/  num_inst; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEDIA_ENT_F_PROC_VIDEO_SCALER ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct vim2m_dev*) ; 
 struct vim2m_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m2m_media_ops ; 
 int /*<<< orphan*/  m2m_ops ; 
 int /*<<< orphan*/  media_device_init (TYPE_5__*) ; 
 int media_device_register (TYPE_5__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct vim2m_dev*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 int v4l2_device_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  v4l2_info (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_init (int /*<<< orphan*/ *) ; 
 int v4l2_m2m_register_media_controller (int /*<<< orphan*/ ,struct video_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_unregister_media_controller (int /*<<< orphan*/ ) ; 
 int video_register_device (struct video_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_set_drvdata (struct video_device*,struct vim2m_dev*) ; 
 int /*<<< orphan*/  video_unregister_device (struct video_device*) ; 
 struct video_device vim2m_videodev ; 

__attribute__((used)) static int vim2m_probe(struct platform_device *pdev)
{
	struct vim2m_dev *dev;
	struct video_device *vfd;
	int ret;

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;

	ret = v4l2_device_register(&pdev->dev, &dev->v4l2_dev);
	if (ret)
		goto error_free;

	atomic_set(&dev->num_inst, 0);
	mutex_init(&dev->dev_mutex);

	dev->vfd = vim2m_videodev;
	vfd = &dev->vfd;
	vfd->lock = &dev->dev_mutex;
	vfd->v4l2_dev = &dev->v4l2_dev;

	ret = video_register_device(vfd, VFL_TYPE_GRABBER, 0);
	if (ret) {
		v4l2_err(&dev->v4l2_dev, "Failed to register video device\n");
		goto error_v4l2;
	}

	video_set_drvdata(vfd, dev);
	v4l2_info(&dev->v4l2_dev,
		  "Device registered as /dev/video%d\n", vfd->num);

	platform_set_drvdata(pdev, dev);

	dev->m2m_dev = v4l2_m2m_init(&m2m_ops);
	if (IS_ERR(dev->m2m_dev)) {
		v4l2_err(&dev->v4l2_dev, "Failed to init mem2mem device\n");
		ret = PTR_ERR(dev->m2m_dev);
		goto error_dev;
	}

#ifdef CONFIG_MEDIA_CONTROLLER
	dev->mdev.dev = &pdev->dev;
	strscpy(dev->mdev.model, "vim2m", sizeof(dev->mdev.model));
	strscpy(dev->mdev.bus_info, "platform:vim2m",
		sizeof(dev->mdev.bus_info));
	media_device_init(&dev->mdev);
	dev->mdev.ops = &m2m_media_ops;
	dev->v4l2_dev.mdev = &dev->mdev;

	ret = v4l2_m2m_register_media_controller(dev->m2m_dev, vfd,
						 MEDIA_ENT_F_PROC_VIDEO_SCALER);
	if (ret) {
		v4l2_err(&dev->v4l2_dev, "Failed to init mem2mem media controller\n");
		goto error_dev;
	}

	ret = media_device_register(&dev->mdev);
	if (ret) {
		v4l2_err(&dev->v4l2_dev, "Failed to register mem2mem media device\n");
		goto error_m2m_mc;
	}
#endif
	return 0;

#ifdef CONFIG_MEDIA_CONTROLLER
error_m2m_mc:
	v4l2_m2m_unregister_media_controller(dev->m2m_dev);
#endif
error_dev:
	video_unregister_device(&dev->vfd);
	/* vim2m_device_release called by video_unregister_device to release various objects */
	return ret;
error_v4l2:
	v4l2_device_unregister(&dev->v4l2_dev);
error_free:
	kfree(dev);

	return ret;
}