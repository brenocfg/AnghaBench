#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  ctrl_handler; int /*<<< orphan*/  name; } ;
struct TYPE_10__ {int minor; int device_caps; TYPE_4__* v4l2_dev; int /*<<< orphan*/ * lock; int /*<<< orphan*/  release; int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/ * fops; int /*<<< orphan*/  name; } ;
struct timb_radio_platform_data {int /*<<< orphan*/  dsp; int /*<<< orphan*/  i2c_adapter; int /*<<< orphan*/  tuner; } ;
struct timbradio {TYPE_4__ v4l2_dev; TYPE_2__ video_dev; TYPE_1__* sd_dsp; int /*<<< orphan*/ * sd_tuner; int /*<<< orphan*/  lock; struct timb_radio_platform_data pdata; } ;
struct TYPE_12__ {struct timb_radio_platform_data* platform_data; } ;
struct platform_device {TYPE_7__ dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  ctrl_handler; } ;

/* Variables and functions */
 char* DRIVER_NAME ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int V4L2_CAP_RADIO ; 
 int V4L2_CAP_TUNER ; 
 int /*<<< orphan*/  VFL_TYPE_RADIO ; 
 int /*<<< orphan*/  dev_err (TYPE_7__*,char*,...) ; 
 struct timbradio* devm_kzalloc (TYPE_7__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_get_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct timbradio*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  timbradio_fops ; 
 int /*<<< orphan*/  timbradio_ioctl_ops ; 
 int v4l2_device_register (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (TYPE_4__*) ; 
 void* v4l2_i2c_new_subdev_board (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_device_release_empty ; 
 int video_register_device (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (TYPE_2__*,struct timbradio*) ; 

__attribute__((used)) static int timbradio_probe(struct platform_device *pdev)
{
	struct timb_radio_platform_data *pdata = pdev->dev.platform_data;
	struct timbradio *tr;
	int err;

	if (!pdata) {
		dev_err(&pdev->dev, "Platform data missing\n");
		err = -EINVAL;
		goto err;
	}

	tr = devm_kzalloc(&pdev->dev, sizeof(*tr), GFP_KERNEL);
	if (!tr) {
		err = -ENOMEM;
		goto err;
	}

	tr->pdata = *pdata;
	mutex_init(&tr->lock);

	strscpy(tr->video_dev.name, "Timberdale Radio",
		sizeof(tr->video_dev.name));
	tr->video_dev.fops = &timbradio_fops;
	tr->video_dev.ioctl_ops = &timbradio_ioctl_ops;
	tr->video_dev.release = video_device_release_empty;
	tr->video_dev.minor = -1;
	tr->video_dev.lock = &tr->lock;
	tr->video_dev.device_caps = V4L2_CAP_TUNER | V4L2_CAP_RADIO;

	strscpy(tr->v4l2_dev.name, DRIVER_NAME, sizeof(tr->v4l2_dev.name));
	err = v4l2_device_register(NULL, &tr->v4l2_dev);
	if (err)
		goto err;

	tr->video_dev.v4l2_dev = &tr->v4l2_dev;

	tr->sd_tuner = v4l2_i2c_new_subdev_board(&tr->v4l2_dev,
		i2c_get_adapter(pdata->i2c_adapter), pdata->tuner, NULL);
	tr->sd_dsp = v4l2_i2c_new_subdev_board(&tr->v4l2_dev,
		i2c_get_adapter(pdata->i2c_adapter), pdata->dsp, NULL);
	if (tr->sd_tuner == NULL || tr->sd_dsp == NULL) {
		err = -ENODEV;
		goto err_video_req;
	}

	tr->v4l2_dev.ctrl_handler = tr->sd_dsp->ctrl_handler;

	err = video_register_device(&tr->video_dev, VFL_TYPE_RADIO, -1);
	if (err) {
		dev_err(&pdev->dev, "Error reg video\n");
		goto err_video_req;
	}

	video_set_drvdata(&tr->video_dev, tr);

	platform_set_drvdata(pdev, tr);
	return 0;

err_video_req:
	v4l2_device_unregister(&tr->v4l2_dev);
err:
	dev_err(&pdev->dev, "Failed to register: %d\n", err);

	return err;
}