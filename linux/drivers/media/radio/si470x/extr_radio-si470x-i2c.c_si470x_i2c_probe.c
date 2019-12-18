#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int error; } ;
struct TYPE_7__ {int device_caps; int /*<<< orphan*/  release; int /*<<< orphan*/ * v4l2_dev; int /*<<< orphan*/ * lock; TYPE_3__* ctrl_handler; } ;
struct si470x_device {int band; scalar_t__ (* set_register ) (struct si470x_device*,size_t) ;int* registers; int buf_size; int /*<<< orphan*/  v4l2_dev; TYPE_3__ hdl; TYPE_1__ videodev; int /*<<< orphan*/  read_queue; scalar_t__ rd_index; scalar_t__ wr_index; int /*<<< orphan*/  buffer; scalar_t__ gpio_reset; int /*<<< orphan*/  lock; int /*<<< orphan*/  vidioc_querycap; int /*<<< orphan*/  fops_release; int /*<<< orphan*/  fops_open; int /*<<< orphan*/  get_register; int /*<<< orphan*/  completion; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 size_t DEVICEID ; 
 int /*<<< orphan*/  DRIVER_NAME ; 
 int EIO ; 
 int ENOMEM ; 
 double FREQ_MUL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 size_t POWERCFG ; 
 int POWERCFG_ENABLE ; 
 int PTR_ERR (scalar_t__) ; 
 int RADIO_FW_VERSION ; 
 size_t SI_CHIPID ; 
 int SI_CHIPID_FIRMWARE ; 
 int V4L2_CAP_HW_FREQ_SEEK ; 
 int V4L2_CAP_RADIO ; 
 int V4L2_CAP_RDS_CAPTURE ; 
 int V4L2_CAP_READWRITE ; 
 int V4L2_CAP_TUNER ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_MUTE ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_VOLUME ; 
 int /*<<< orphan*/  VFL_TYPE_RADIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ devm_gpiod_get_optional (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kmalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct si470x_device* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct si470x_device*) ; 
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct si470x_device*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radio_nr ; 
 int rds_buf ; 
 int /*<<< orphan*/  si470x_ctrl_ops ; 
 int /*<<< orphan*/  si470x_fops_open ; 
 int /*<<< orphan*/  si470x_fops_release ; 
 scalar_t__ si470x_get_all_registers (struct si470x_device*) ; 
 int /*<<< orphan*/  si470x_get_register ; 
 int /*<<< orphan*/  si470x_i2c_interrupt ; 
 int /*<<< orphan*/  si470x_set_freq (struct si470x_device*,double) ; 
 scalar_t__ si470x_set_register (struct si470x_device*,size_t) ; 
 TYPE_1__ si470x_viddev_template ; 
 int /*<<< orphan*/  si470x_vidioc_querycap ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_3__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_3__*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int v4l2_device_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_device_release_empty ; 
 int video_register_device (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_set_drvdata (TYPE_1__*,struct si470x_device*) ; 

__attribute__((used)) static int si470x_i2c_probe(struct i2c_client *client)
{
	struct si470x_device *radio;
	int retval = 0;
	unsigned char version_warning = 0;

	/* private data allocation and initialization */
	radio = devm_kzalloc(&client->dev, sizeof(*radio), GFP_KERNEL);
	if (!radio) {
		retval = -ENOMEM;
		goto err_initial;
	}

	radio->client = client;
	radio->band = 1; /* Default to 76 - 108 MHz */
	mutex_init(&radio->lock);
	init_completion(&radio->completion);

	radio->get_register = si470x_get_register;
	radio->set_register = si470x_set_register;
	radio->fops_open = si470x_fops_open;
	radio->fops_release = si470x_fops_release;
	radio->vidioc_querycap = si470x_vidioc_querycap;

	retval = v4l2_device_register(&client->dev, &radio->v4l2_dev);
	if (retval < 0) {
		dev_err(&client->dev, "couldn't register v4l2_device\n");
		goto err_initial;
	}

	v4l2_ctrl_handler_init(&radio->hdl, 2);
	v4l2_ctrl_new_std(&radio->hdl, &si470x_ctrl_ops,
			V4L2_CID_AUDIO_MUTE, 0, 1, 1, 1);
	v4l2_ctrl_new_std(&radio->hdl, &si470x_ctrl_ops,
			V4L2_CID_AUDIO_VOLUME, 0, 15, 1, 15);
	if (radio->hdl.error) {
		retval = radio->hdl.error;
		dev_err(&client->dev, "couldn't register control\n");
		goto err_dev;
	}

	/* video device initialization */
	radio->videodev = si470x_viddev_template;
	radio->videodev.ctrl_handler = &radio->hdl;
	radio->videodev.lock = &radio->lock;
	radio->videodev.v4l2_dev = &radio->v4l2_dev;
	radio->videodev.release = video_device_release_empty;
	radio->videodev.device_caps =
		V4L2_CAP_HW_FREQ_SEEK | V4L2_CAP_READWRITE | V4L2_CAP_TUNER |
		V4L2_CAP_RADIO | V4L2_CAP_RDS_CAPTURE;
	video_set_drvdata(&radio->videodev, radio);

	radio->gpio_reset = devm_gpiod_get_optional(&client->dev, "reset",
						    GPIOD_OUT_LOW);
	if (IS_ERR(radio->gpio_reset)) {
		retval = PTR_ERR(radio->gpio_reset);
		dev_err(&client->dev, "Failed to request gpio: %d\n", retval);
		goto err_all;
	}

	if (radio->gpio_reset)
		gpiod_set_value(radio->gpio_reset, 1);

	/* power up : need 110ms */
	radio->registers[POWERCFG] = POWERCFG_ENABLE;
	if (si470x_set_register(radio, POWERCFG) < 0) {
		retval = -EIO;
		goto err_all;
	}
	msleep(110);

	/* get device and chip versions */
	if (si470x_get_all_registers(radio) < 0) {
		retval = -EIO;
		goto err_all;
	}
	dev_info(&client->dev, "DeviceID=0x%4.4hx ChipID=0x%4.4hx\n",
			radio->registers[DEVICEID], radio->registers[SI_CHIPID]);
	if ((radio->registers[SI_CHIPID] & SI_CHIPID_FIRMWARE) < RADIO_FW_VERSION) {
		dev_warn(&client->dev,
			"This driver is known to work with firmware version %hu,\n",
			RADIO_FW_VERSION);
		dev_warn(&client->dev,
			"but the device has firmware version %hu.\n",
			radio->registers[SI_CHIPID] & SI_CHIPID_FIRMWARE);
		version_warning = 1;
	}

	/* give out version warning */
	if (version_warning == 1) {
		dev_warn(&client->dev,
			"If you have some trouble using this driver,\n");
		dev_warn(&client->dev,
			"please report to V4L ML at linux-media@vger.kernel.org\n");
	}

	/* set initial frequency */
	si470x_set_freq(radio, 87.5 * FREQ_MUL); /* available in all regions */

	/* rds buffer allocation */
	radio->buf_size = rds_buf * 3;
	radio->buffer = devm_kmalloc(&client->dev, radio->buf_size, GFP_KERNEL);
	if (!radio->buffer) {
		retval = -EIO;
		goto err_all;
	}

	/* rds buffer configuration */
	radio->wr_index = 0;
	radio->rd_index = 0;
	init_waitqueue_head(&radio->read_queue);

	retval = devm_request_threaded_irq(&client->dev, client->irq, NULL,
					   si470x_i2c_interrupt,
					   IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					   DRIVER_NAME, radio);
	if (retval) {
		dev_err(&client->dev, "Failed to register interrupt\n");
		goto err_all;
	}

	/* register video device */
	retval = video_register_device(&radio->videodev, VFL_TYPE_RADIO,
			radio_nr);
	if (retval) {
		dev_warn(&client->dev, "Could not register video device\n");
		goto err_all;
	}
	i2c_set_clientdata(client, radio);

	return 0;
err_all:
	v4l2_ctrl_handler_free(&radio->hdl);
err_dev:
	v4l2_device_unregister(&radio->v4l2_dev);
err_initial:
	return retval;
}