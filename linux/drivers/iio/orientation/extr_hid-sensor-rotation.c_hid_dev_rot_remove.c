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
struct iio_dev {int dummy; } ;
struct hid_sensor_hub_device {int /*<<< orphan*/  usage; } ;
struct dev_rot_state {int /*<<< orphan*/  common_attributes; } ;

/* Variables and functions */
 int /*<<< orphan*/  hid_sensor_remove_trigger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct dev_rot_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 struct iio_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sensor_hub_remove_callback (struct hid_sensor_hub_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hid_dev_rot_remove(struct platform_device *pdev)
{
	struct hid_sensor_hub_device *hsdev = pdev->dev.platform_data;
	struct iio_dev *indio_dev = platform_get_drvdata(pdev);
	struct dev_rot_state *rot_state = iio_priv(indio_dev);

	sensor_hub_remove_callback(hsdev, hsdev->usage);
	iio_device_unregister(indio_dev);
	hid_sensor_remove_trigger(&rot_state->common_attributes);
	iio_triggered_buffer_cleanup(indio_dev);

	return 0;
}