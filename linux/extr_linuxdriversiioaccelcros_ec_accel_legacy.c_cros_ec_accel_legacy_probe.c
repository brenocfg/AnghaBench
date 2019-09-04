#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {struct device* parent; } ;
struct iio_dev {int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_2__ dev; int /*<<< orphan*/  num_channels; TYPE_3__* channels; int /*<<< orphan*/  name; } ;
struct cros_ec_sensor_platform {scalar_t__ sensor_num; } ;
struct cros_ec_dev {TYPE_1__* ec_dev; } ;
struct cros_ec_accel_legacy_state {scalar_t__ sensor_num; int* sign; TYPE_1__* ec; } ;
struct TYPE_7__ {int scan_index; } ;
struct TYPE_5__ {int /*<<< orphan*/  cmd_readmem; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_3__*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int MAX_AXIS ; 
 scalar_t__ MOTIONSENSE_LOC_LID ; 
#define  X 130 
#define  Y 129 
#define  Z 128 
 int /*<<< orphan*/  cros_ec_accel_legacy_capture ; 
 int /*<<< orphan*/  cros_ec_accel_legacy_info ; 
 struct cros_ec_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct cros_ec_sensor_platform* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int devm_iio_device_register (struct device*,struct iio_dev*) ; 
 int devm_iio_triggered_buffer_setup (struct device*,struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* ec_accel_channels ; 
 struct cros_ec_accel_legacy_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct iio_dev*) ; 

__attribute__((used)) static int cros_ec_accel_legacy_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct cros_ec_dev *ec = dev_get_drvdata(dev->parent);
	struct cros_ec_sensor_platform *sensor_platform = dev_get_platdata(dev);
	struct iio_dev *indio_dev;
	struct cros_ec_accel_legacy_state *state;
	int ret, i;

	if (!ec || !ec->ec_dev) {
		dev_warn(&pdev->dev, "No EC device found.\n");
		return -EINVAL;
	}

	if (!ec->ec_dev->cmd_readmem) {
		dev_warn(&pdev->dev, "EC does not support direct reads.\n");
		return -EINVAL;
	}

	indio_dev = devm_iio_device_alloc(&pdev->dev, sizeof(*state));
	if (!indio_dev)
		return -ENOMEM;

	platform_set_drvdata(pdev, indio_dev);
	state = iio_priv(indio_dev);
	state->ec = ec->ec_dev;
	state->sensor_num = sensor_platform->sensor_num;

	indio_dev->dev.parent = dev;
	indio_dev->name = pdev->name;
	indio_dev->channels = ec_accel_channels;
	/*
	 * Present the channel using HTML5 standard:
	 * need to invert X and Y and invert some lid axis.
	 */
	for (i = X ; i < MAX_AXIS; i++) {
		switch (i) {
		case X:
			ec_accel_channels[X].scan_index = Y;
		case Y:
			ec_accel_channels[Y].scan_index = X;
		case Z:
			ec_accel_channels[Z].scan_index = Z;
		}
		if (state->sensor_num == MOTIONSENSE_LOC_LID && i != Y)
			state->sign[i] = -1;
		else
			state->sign[i] = 1;
	}
	indio_dev->num_channels = ARRAY_SIZE(ec_accel_channels);
	indio_dev->dev.parent = &pdev->dev;
	indio_dev->info = &cros_ec_accel_legacy_info;
	indio_dev->modes = INDIO_DIRECT_MODE;

	ret = devm_iio_triggered_buffer_setup(dev, indio_dev, NULL,
					      cros_ec_accel_legacy_capture,
					      NULL);
	if (ret)
		return ret;

	return devm_iio_device_register(dev, indio_dev);
}