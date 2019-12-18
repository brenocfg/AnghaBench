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
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;
struct iio_dev {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/ * info; } ;
struct cros_ec_sensors_core_state {scalar_t__ loc; int* sign; int /*<<< orphan*/  read_ec_sensors_data; TYPE_1__* ec; } ;
struct cros_ec_dev {int /*<<< orphan*/  ec_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * cmd_readmem; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 size_t CROS_EC_SENSOR_X ; 
 size_t CROS_EC_SENSOR_Z ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ MOTIONSENSE_LOC_LID ; 
 int /*<<< orphan*/  cros_ec_accel_legacy_channels ; 
 int /*<<< orphan*/  cros_ec_accel_legacy_info ; 
 int /*<<< orphan*/  cros_ec_accel_legacy_read_cmd ; 
 int /*<<< orphan*/  cros_ec_sensors_capture ; 
 int cros_ec_sensors_core_init (struct platform_device*,struct iio_dev*,int) ; 
 int /*<<< orphan*/  cros_ec_sensors_read_lpc ; 
 struct cros_ec_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int devm_iio_device_register (struct device*,struct iio_dev*) ; 
 int devm_iio_triggered_buffer_setup (struct device*,struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cros_ec_sensors_core_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int cros_ec_accel_legacy_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct cros_ec_dev *ec = dev_get_drvdata(dev->parent);
	struct iio_dev *indio_dev;
	struct cros_ec_sensors_core_state *state;
	int ret;

	if (!ec || !ec->ec_dev) {
		dev_warn(&pdev->dev, "No EC device found.\n");
		return -EINVAL;
	}

	indio_dev = devm_iio_device_alloc(&pdev->dev, sizeof(*state));
	if (!indio_dev)
		return -ENOMEM;

	ret = cros_ec_sensors_core_init(pdev, indio_dev, true);
	if (ret)
		return ret;

	indio_dev->info = &cros_ec_accel_legacy_info;
	state = iio_priv(indio_dev);

	if (state->ec->cmd_readmem != NULL)
		state->read_ec_sensors_data = cros_ec_sensors_read_lpc;
	else
		state->read_ec_sensors_data = cros_ec_accel_legacy_read_cmd;

	indio_dev->channels = cros_ec_accel_legacy_channels;
	indio_dev->num_channels = ARRAY_SIZE(cros_ec_accel_legacy_channels);
	/* The lid sensor needs to be presented inverted. */
	if (state->loc == MOTIONSENSE_LOC_LID) {
		state->sign[CROS_EC_SENSOR_X] = -1;
		state->sign[CROS_EC_SENSOR_Z] = -1;
	}

	ret = devm_iio_triggered_buffer_setup(dev, indio_dev, NULL,
			cros_ec_sensors_capture, NULL);
	if (ret)
		return ret;

	return devm_iio_device_register(dev, indio_dev);
}