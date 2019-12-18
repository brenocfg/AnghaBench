#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_5__* mdev; int /*<<< orphan*/  release; } ;
struct TYPE_8__ {int /*<<< orphan*/  m2m_dev; int /*<<< orphan*/  vfd; } ;
struct TYPE_9__ {int /*<<< orphan*/ * ops; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  model; int /*<<< orphan*/ * dev; } ;
struct vicodec_dev {TYPE_1__ v4l2_dev; TYPE_4__ stateful_enc; TYPE_4__ stateful_dec; TYPE_4__ stateless_dec; TYPE_5__ mdev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MEDIA_ENT_F_PROC_VIDEO_DECODER ; 
 int /*<<< orphan*/  MEDIA_ENT_F_PROC_VIDEO_ENCODER ; 
 int /*<<< orphan*/  kfree (struct vicodec_dev*) ; 
 struct vicodec_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_device_init (TYPE_5__*) ; 
 int media_device_register (TYPE_5__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct vicodec_dev*) ; 
 scalar_t__ register_instance (struct vicodec_dev*,TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 int v4l2_device_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_err (TYPE_1__*,char*) ; 
 int v4l2_m2m_register_media_controller (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_unregister_media_controller (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vicodec_m2m_media_ops ; 
 int /*<<< orphan*/  vicodec_v4l2_dev_release ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vicodec_probe(struct platform_device *pdev)
{
	struct vicodec_dev *dev;
	int ret;

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;

	ret = v4l2_device_register(&pdev->dev, &dev->v4l2_dev);
	if (ret)
		goto free_dev;

	dev->v4l2_dev.release = vicodec_v4l2_dev_release;

#ifdef CONFIG_MEDIA_CONTROLLER
	dev->mdev.dev = &pdev->dev;
	strscpy(dev->mdev.model, "vicodec", sizeof(dev->mdev.model));
	strscpy(dev->mdev.bus_info, "platform:vicodec",
		sizeof(dev->mdev.bus_info));
	media_device_init(&dev->mdev);
	dev->mdev.ops = &vicodec_m2m_media_ops;
	dev->v4l2_dev.mdev = &dev->mdev;
#endif

	platform_set_drvdata(pdev, dev);

	if (register_instance(dev, &dev->stateful_enc,
			      "stateful-encoder", true))
		goto unreg_dev;

	if (register_instance(dev, &dev->stateful_dec,
			      "stateful-decoder", false))
		goto unreg_sf_enc;

	if (register_instance(dev, &dev->stateless_dec,
			      "stateless-decoder", false))
		goto unreg_sf_dec;

#ifdef CONFIG_MEDIA_CONTROLLER
	ret = v4l2_m2m_register_media_controller(dev->stateful_enc.m2m_dev,
						 &dev->stateful_enc.vfd,
						 MEDIA_ENT_F_PROC_VIDEO_ENCODER);
	if (ret) {
		v4l2_err(&dev->v4l2_dev, "Failed to init mem2mem media controller for enc\n");
		goto unreg_m2m;
	}

	ret = v4l2_m2m_register_media_controller(dev->stateful_dec.m2m_dev,
						 &dev->stateful_dec.vfd,
						 MEDIA_ENT_F_PROC_VIDEO_DECODER);
	if (ret) {
		v4l2_err(&dev->v4l2_dev, "Failed to init mem2mem media controller for dec\n");
		goto unreg_m2m_sf_enc_mc;
	}

	ret = v4l2_m2m_register_media_controller(dev->stateless_dec.m2m_dev,
						 &dev->stateless_dec.vfd,
						 MEDIA_ENT_F_PROC_VIDEO_DECODER);
	if (ret) {
		v4l2_err(&dev->v4l2_dev, "Failed to init mem2mem media controller for stateless dec\n");
		goto unreg_m2m_sf_dec_mc;
	}

	ret = media_device_register(&dev->mdev);
	if (ret) {
		v4l2_err(&dev->v4l2_dev, "Failed to register mem2mem media device\n");
		goto unreg_m2m_sl_dec_mc;
	}
#endif
	return 0;

#ifdef CONFIG_MEDIA_CONTROLLER
unreg_m2m_sl_dec_mc:
	v4l2_m2m_unregister_media_controller(dev->stateless_dec.m2m_dev);
unreg_m2m_sf_dec_mc:
	v4l2_m2m_unregister_media_controller(dev->stateful_dec.m2m_dev);
unreg_m2m_sf_enc_mc:
	v4l2_m2m_unregister_media_controller(dev->stateful_enc.m2m_dev);
unreg_m2m:
	video_unregister_device(&dev->stateless_dec.vfd);
	v4l2_m2m_release(dev->stateless_dec.m2m_dev);
#endif
unreg_sf_dec:
	video_unregister_device(&dev->stateful_dec.vfd);
	v4l2_m2m_release(dev->stateful_dec.m2m_dev);
unreg_sf_enc:
	video_unregister_device(&dev->stateful_enc.vfd);
	v4l2_m2m_release(dev->stateful_enc.m2m_dev);
unreg_dev:
	v4l2_device_unregister(&dev->v4l2_dev);
free_dev:
	kfree(dev);

	return ret;
}