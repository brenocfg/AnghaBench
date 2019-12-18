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
struct video_device {char* name; int /*<<< orphan*/  num; TYPE_1__* v4l2_dev; int /*<<< orphan*/ * lock; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {TYPE_5__* mdev; } ;
struct TYPE_8__ {int /*<<< orphan*/ * ops; int /*<<< orphan*/  model; int /*<<< orphan*/ * dev; } ;
struct cedrus_dev {TYPE_1__ v4l2_dev; int /*<<< orphan*/  m2m_dev; struct video_device vfd; TYPE_5__ mdev; int /*<<< orphan*/  dev_mutex; int /*<<< orphan*/ ** dec_ops; struct platform_device* pdev; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 size_t CEDRUS_CODEC_H264 ; 
 size_t CEDRUS_CODEC_MPEG2 ; 
 int /*<<< orphan*/  CEDRUS_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEDIA_ENT_F_PROC_VIDEO_DECODER ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  cedrus_dec_ops_h264 ; 
 int /*<<< orphan*/  cedrus_dec_ops_mpeg2 ; 
 int cedrus_hw_probe (struct cedrus_dev*) ; 
 int /*<<< orphan*/  cedrus_m2m_media_ops ; 
 int /*<<< orphan*/  cedrus_m2m_ops ; 
 struct video_device cedrus_video_device ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct cedrus_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_device_init (TYPE_5__*) ; 
 int media_device_register (TYPE_5__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct cedrus_dev*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int v4l2_device_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  v4l2_info (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_init (int /*<<< orphan*/ *) ; 
 int v4l2_m2m_register_media_controller (int /*<<< orphan*/ ,struct video_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_unregister_media_controller (int /*<<< orphan*/ ) ; 
 int video_register_device (struct video_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_set_drvdata (struct video_device*,struct cedrus_dev*) ; 
 int /*<<< orphan*/  video_unregister_device (struct video_device*) ; 

__attribute__((used)) static int cedrus_probe(struct platform_device *pdev)
{
	struct cedrus_dev *dev;
	struct video_device *vfd;
	int ret;

	dev = devm_kzalloc(&pdev->dev, sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;

	dev->vfd = cedrus_video_device;
	dev->dev = &pdev->dev;
	dev->pdev = pdev;

	ret = cedrus_hw_probe(dev);
	if (ret) {
		dev_err(&pdev->dev, "Failed to probe hardware\n");
		return ret;
	}

	dev->dec_ops[CEDRUS_CODEC_MPEG2] = &cedrus_dec_ops_mpeg2;
	dev->dec_ops[CEDRUS_CODEC_H264] = &cedrus_dec_ops_h264;

	mutex_init(&dev->dev_mutex);

	ret = v4l2_device_register(&pdev->dev, &dev->v4l2_dev);
	if (ret) {
		dev_err(&pdev->dev, "Failed to register V4L2 device\n");
		return ret;
	}

	vfd = &dev->vfd;
	vfd->lock = &dev->dev_mutex;
	vfd->v4l2_dev = &dev->v4l2_dev;

	snprintf(vfd->name, sizeof(vfd->name), "%s", cedrus_video_device.name);
	video_set_drvdata(vfd, dev);

	dev->m2m_dev = v4l2_m2m_init(&cedrus_m2m_ops);
	if (IS_ERR(dev->m2m_dev)) {
		v4l2_err(&dev->v4l2_dev,
			 "Failed to initialize V4L2 M2M device\n");
		ret = PTR_ERR(dev->m2m_dev);

		goto err_v4l2;
	}

	dev->mdev.dev = &pdev->dev;
	strscpy(dev->mdev.model, CEDRUS_NAME, sizeof(dev->mdev.model));

	media_device_init(&dev->mdev);
	dev->mdev.ops = &cedrus_m2m_media_ops;
	dev->v4l2_dev.mdev = &dev->mdev;

	ret = video_register_device(vfd, VFL_TYPE_GRABBER, 0);
	if (ret) {
		v4l2_err(&dev->v4l2_dev, "Failed to register video device\n");
		goto err_m2m;
	}

	v4l2_info(&dev->v4l2_dev,
		  "Device registered as /dev/video%d\n", vfd->num);

	ret = v4l2_m2m_register_media_controller(dev->m2m_dev, vfd,
						 MEDIA_ENT_F_PROC_VIDEO_DECODER);
	if (ret) {
		v4l2_err(&dev->v4l2_dev,
			 "Failed to initialize V4L2 M2M media controller\n");
		goto err_video;
	}

	ret = media_device_register(&dev->mdev);
	if (ret) {
		v4l2_err(&dev->v4l2_dev, "Failed to register media device\n");
		goto err_m2m_mc;
	}

	platform_set_drvdata(pdev, dev);

	return 0;

err_m2m_mc:
	v4l2_m2m_unregister_media_controller(dev->m2m_dev);
err_video:
	video_unregister_device(&dev->vfd);
err_m2m:
	v4l2_m2m_release(dev->m2m_dev);
err_v4l2:
	v4l2_device_unregister(&dev->v4l2_dev);

	return ret;
}