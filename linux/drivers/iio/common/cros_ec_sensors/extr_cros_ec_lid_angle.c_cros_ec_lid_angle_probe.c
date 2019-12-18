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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct iio_dev {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/ * info; } ;
struct TYPE_2__ {int /*<<< orphan*/  read_ec_sensors_data; } ;
struct cros_ec_lid_angle_state {TYPE_1__ core; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  cros_ec_lid_angle_channels ; 
 int /*<<< orphan*/  cros_ec_lid_angle_info ; 
 int /*<<< orphan*/  cros_ec_sensors_capture ; 
 int cros_ec_sensors_core_init (struct platform_device*,struct iio_dev*,int) ; 
 int /*<<< orphan*/  cros_ec_sensors_read_lid_angle ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int devm_iio_device_register (struct device*,struct iio_dev*) ; 
 int devm_iio_triggered_buffer_setup (struct device*,struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cros_ec_lid_angle_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int cros_ec_lid_angle_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct iio_dev *indio_dev;
	struct cros_ec_lid_angle_state *state;
	int ret;

	indio_dev = devm_iio_device_alloc(dev, sizeof(*state));
	if (!indio_dev)
		return -ENOMEM;

	ret = cros_ec_sensors_core_init(pdev, indio_dev, false);
	if (ret)
		return ret;

	indio_dev->info = &cros_ec_lid_angle_info;
	state = iio_priv(indio_dev);
	indio_dev->channels = cros_ec_lid_angle_channels;
	indio_dev->num_channels = ARRAY_SIZE(cros_ec_lid_angle_channels);

	state->core.read_ec_sensors_data = cros_ec_sensors_read_lid_angle;

	ret = devm_iio_triggered_buffer_setup(dev, indio_dev, NULL,
			cros_ec_sensors_capture, NULL);
	if (ret)
		return ret;

	return devm_iio_device_register(dev, indio_dev);
}