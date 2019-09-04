#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {struct hid_sensor_hub_device* platform_data; } ;
struct platform_device {TYPE_6__ dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  data_ready; struct platform_device* pdev; struct hid_sensor_hub_device* hsdev; } ;
struct TYPE_9__ {struct platform_device* pdev; int /*<<< orphan*/  capture_sample; int /*<<< orphan*/  send_event; } ;
struct magn_3d_state {TYPE_3__ magn_flux_attributes; TYPE_2__ callbacks; TYPE_3__ rot_attributes; } ;
struct TYPE_8__ {TYPE_6__* parent; } ;
struct iio_dev {int num_channels; char* name; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; struct iio_chan_spec* channels; } ;
struct iio_chan_spec {int dummy; } ;
struct hid_sensor_hub_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HID_USAGE_SENSOR_COMPASS_3D ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_6__*,char*) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_6__*,int) ; 
 int hid_sensor_parse_common_attributes (struct hid_sensor_hub_device*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  hid_sensor_remove_trigger (TYPE_3__*) ; 
 int hid_sensor_setup_trigger (struct iio_dev*,char*,TYPE_3__*) ; 
 int iio_device_register (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_pollfunc_store_time ; 
 struct magn_3d_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int iio_triggered_buffer_setup (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  magn_3d_capture_sample ; 
 int /*<<< orphan*/  magn_3d_info ; 
 int magn_3d_parse_report (struct platform_device*,struct hid_sensor_hub_device*,struct iio_chan_spec**,int*,int /*<<< orphan*/ ,struct magn_3d_state*) ; 
 int /*<<< orphan*/  magn_3d_proc_event ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct iio_dev*) ; 
 int sensor_hub_register_callback (struct hid_sensor_hub_device*,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int hid_magn_3d_probe(struct platform_device *pdev)
{
	int ret = 0;
	static char *name = "magn_3d";
	struct iio_dev *indio_dev;
	struct magn_3d_state *magn_state;
	struct hid_sensor_hub_device *hsdev = pdev->dev.platform_data;
	struct iio_chan_spec *channels;
	int chan_count = 0;

	indio_dev = devm_iio_device_alloc(&pdev->dev,
					  sizeof(struct magn_3d_state));
	if (indio_dev == NULL)
		return -ENOMEM;

	platform_set_drvdata(pdev, indio_dev);

	magn_state = iio_priv(indio_dev);
	magn_state->magn_flux_attributes.hsdev = hsdev;
	magn_state->magn_flux_attributes.pdev = pdev;

	ret = hid_sensor_parse_common_attributes(hsdev,
				HID_USAGE_SENSOR_COMPASS_3D,
				&magn_state->magn_flux_attributes);
	if (ret) {
		dev_err(&pdev->dev, "failed to setup common attributes\n");
		return ret;
	}
	magn_state->rot_attributes = magn_state->magn_flux_attributes;

	ret = magn_3d_parse_report(pdev, hsdev,
				&channels, &chan_count,
				HID_USAGE_SENSOR_COMPASS_3D, magn_state);
	if (ret) {
		dev_err(&pdev->dev, "failed to parse report\n");
		return ret;
	}

	indio_dev->channels = channels;
	indio_dev->num_channels = chan_count;
	indio_dev->dev.parent = &pdev->dev;
	indio_dev->info = &magn_3d_info;
	indio_dev->name = name;
	indio_dev->modes = INDIO_DIRECT_MODE;

	ret = iio_triggered_buffer_setup(indio_dev, &iio_pollfunc_store_time,
		NULL, NULL);
	if (ret) {
		dev_err(&pdev->dev, "failed to initialize trigger buffer\n");
		return ret;
	}
	atomic_set(&magn_state->magn_flux_attributes.data_ready, 0);
	ret = hid_sensor_setup_trigger(indio_dev, name,
					&magn_state->magn_flux_attributes);
	if (ret < 0) {
		dev_err(&pdev->dev, "trigger setup failed\n");
		goto error_unreg_buffer_funcs;
	}

	ret = iio_device_register(indio_dev);
	if (ret) {
		dev_err(&pdev->dev, "device register failed\n");
		goto error_remove_trigger;
	}

	magn_state->callbacks.send_event = magn_3d_proc_event;
	magn_state->callbacks.capture_sample = magn_3d_capture_sample;
	magn_state->callbacks.pdev = pdev;
	ret = sensor_hub_register_callback(hsdev, HID_USAGE_SENSOR_COMPASS_3D,
					&magn_state->callbacks);
	if (ret < 0) {
		dev_err(&pdev->dev, "callback reg failed\n");
		goto error_iio_unreg;
	}

	return ret;

error_iio_unreg:
	iio_device_unregister(indio_dev);
error_remove_trigger:
	hid_sensor_remove_trigger(&magn_state->magn_flux_attributes);
error_unreg_buffer_funcs:
	iio_triggered_buffer_cleanup(indio_dev);
	return ret;
}