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
struct temperature_state {int /*<<< orphan*/  common_attributes; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct iio_dev {int dummy; } ;
struct hid_sensor_hub_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_USAGE_SENSOR_TEMPERATURE ; 
 struct hid_sensor_hub_device* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_sensor_remove_trigger (int /*<<< orphan*/ *) ; 
 struct temperature_state* iio_priv (struct iio_dev*) ; 
 struct iio_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sensor_hub_remove_callback (struct hid_sensor_hub_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hid_temperature_remove(struct platform_device *pdev)
{
	struct hid_sensor_hub_device *hsdev = dev_get_platdata(&pdev->dev);
	struct iio_dev *indio_dev = platform_get_drvdata(pdev);
	struct temperature_state *temp_st = iio_priv(indio_dev);

	sensor_hub_remove_callback(hsdev, HID_USAGE_SENSOR_TEMPERATURE);
	hid_sensor_remove_trigger(&temp_st->common_attributes);

	return 0;
}