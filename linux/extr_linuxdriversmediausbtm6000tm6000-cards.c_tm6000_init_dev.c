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
struct v4l2_frequency {int frequency; int /*<<< orphan*/  type; scalar_t__ tuner; } ;
struct TYPE_2__ {scalar_t__ has_tda9874; } ;
struct tm6000_core {int width; int height; int freq; int /*<<< orphan*/  lock; int /*<<< orphan*/  i2c_adap; int /*<<< orphan*/  v4l2_dev; TYPE_1__ caps; struct v4l2_frequency* norm; int /*<<< orphan*/  model; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_ADDR_TDA9874 ; 
 struct v4l2_frequency* V4L2_STD_NTSC_M ; 
 int /*<<< orphan*/  V4L2_TUNER_ANALOG_TV ; 
 int fill_board_specific_data (struct tm6000_core*) ; 
 int /*<<< orphan*/  is_generic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  request_modules (struct tm6000_core*) ; 
 int /*<<< orphan*/  s_frequency ; 
 int /*<<< orphan*/  s_std ; 
 int /*<<< orphan*/  tm6000_add_into_devlist (struct tm6000_core*) ; 
 int /*<<< orphan*/  tm6000_config_tuner (struct tm6000_core*) ; 
 int tm6000_i2c_register (struct tm6000_core*) ; 
 int /*<<< orphan*/  tm6000_init_extension (struct tm6000_core*) ; 
 int /*<<< orphan*/  tm6000_ir_init (struct tm6000_core*) ; 
 int tm6000_v4l2_register (struct tm6000_core*) ; 
 int /*<<< orphan*/  tuner ; 
 int /*<<< orphan*/  use_alternative_detection_method (struct tm6000_core*) ; 
 int /*<<< orphan*/  v4l2_device_call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_frequency*) ; 
 int /*<<< orphan*/  v4l2_i2c_new_subdev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int tm6000_init_dev(struct tm6000_core *dev)
{
	struct v4l2_frequency f;
	int rc = 0;

	mutex_init(&dev->lock);
	mutex_lock(&dev->lock);

	if (!is_generic(dev->model)) {
		rc = fill_board_specific_data(dev);
		if (rc < 0)
			goto err;

		/* register i2c bus */
		rc = tm6000_i2c_register(dev);
		if (rc < 0)
			goto err;
	} else {
		/* register i2c bus */
		rc = tm6000_i2c_register(dev);
		if (rc < 0)
			goto err;

		use_alternative_detection_method(dev);

		rc = fill_board_specific_data(dev);
		if (rc < 0)
			goto err;
	}

	/* Default values for STD and resolutions */
	dev->width = 720;
	dev->height = 480;
	dev->norm = V4L2_STD_NTSC_M;

	/* Configure tuner */
	tm6000_config_tuner(dev);

	/* Set video standard */
	v4l2_device_call_all(&dev->v4l2_dev, 0, video, s_std, dev->norm);

	/* Set tuner frequency - also loads firmware on xc2028/xc3028 */
	f.tuner = 0;
	f.type = V4L2_TUNER_ANALOG_TV;
	f.frequency = 3092;	/* 193.25 MHz */
	dev->freq = f.frequency;
	v4l2_device_call_all(&dev->v4l2_dev, 0, tuner, s_frequency, &f);

	if (dev->caps.has_tda9874)
		v4l2_i2c_new_subdev(&dev->v4l2_dev, &dev->i2c_adap,
			"tvaudio", I2C_ADDR_TDA9874, NULL);

	/* register and initialize V4L2 */
	rc = tm6000_v4l2_register(dev);
	if (rc < 0)
		goto err;

	tm6000_add_into_devlist(dev);
	tm6000_init_extension(dev);

	tm6000_ir_init(dev);

	request_modules(dev);

	mutex_unlock(&dev->lock);
	return 0;

err:
	mutex_unlock(&dev->lock);
	return rc;
}