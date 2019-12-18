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
struct TYPE_2__ {struct hid_sensor_hub_device* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct iio_dev {int /*<<< orphan*/  channels; } ;
struct hid_sensor_hub_device {int dummy; } ;
struct gyro_3d_state {int /*<<< orphan*/  common_attributes; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_USAGE_SENSOR_GYRO_3D ; 
 int /*<<< orphan*/  hid_sensor_remove_trigger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct gyro_3d_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct iio_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sensor_hub_remove_callback (struct hid_sensor_hub_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hid_gyro_3d_remove(struct platform_device *pdev)
{
	struct hid_sensor_hub_device *hsdev = pdev->dev.platform_data;
	struct iio_dev *indio_dev = platform_get_drvdata(pdev);
	struct gyro_3d_state *gyro_state = iio_priv(indio_dev);

	sensor_hub_remove_callback(hsdev, HID_USAGE_SENSOR_GYRO_3D);
	iio_device_unregister(indio_dev);
	hid_sensor_remove_trigger(&gyro_state->common_attributes);
	iio_triggered_buffer_cleanup(indio_dev);
	kfree(indio_dev->channels);

	return 0;
}