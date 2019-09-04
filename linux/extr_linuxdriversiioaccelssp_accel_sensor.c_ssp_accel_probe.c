#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ssp_sensor_data {int /*<<< orphan*/  type; int /*<<< orphan*/  process_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; TYPE_2__* parent; } ;
struct iio_dev {int /*<<< orphan*/ * setup_ops; int /*<<< orphan*/  available_scan_masks; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; int /*<<< orphan*/  name; } ;
struct iio_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_BUFFER_SOFTWARE ; 
 int /*<<< orphan*/  SSP_ACCELEROMETER_SENSOR ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_2__*,int) ; 
 int devm_iio_device_register (TYPE_2__*,struct iio_dev*) ; 
 struct iio_buffer* devm_iio_kfifo_allocate (TYPE_2__*) ; 
 int /*<<< orphan*/  iio_device_attach_buffer (struct iio_dev*,struct iio_buffer*) ; 
 struct ssp_sensor_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct iio_dev*) ; 
 int /*<<< orphan*/  ssp_acc_channels ; 
 int /*<<< orphan*/  ssp_accel_buffer_ops ; 
 int /*<<< orphan*/  ssp_accel_device_name ; 
 int /*<<< orphan*/  ssp_accel_iio_info ; 
 int /*<<< orphan*/  ssp_accel_scan_mask ; 
 int /*<<< orphan*/  ssp_process_accel_data ; 
 int /*<<< orphan*/  ssp_register_consumer (struct iio_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssp_accel_probe(struct platform_device *pdev)
{
	int ret;
	struct iio_dev *indio_dev;
	struct ssp_sensor_data *spd;
	struct iio_buffer *buffer;

	indio_dev = devm_iio_device_alloc(&pdev->dev, sizeof(*spd));
	if (!indio_dev)
		return -ENOMEM;

	spd = iio_priv(indio_dev);

	spd->process_data = ssp_process_accel_data;
	spd->type = SSP_ACCELEROMETER_SENSOR;

	indio_dev->name = ssp_accel_device_name;
	indio_dev->dev.parent = &pdev->dev;
	indio_dev->dev.of_node = pdev->dev.of_node;
	indio_dev->info = &ssp_accel_iio_info;
	indio_dev->modes = INDIO_BUFFER_SOFTWARE;
	indio_dev->channels = ssp_acc_channels;
	indio_dev->num_channels = ARRAY_SIZE(ssp_acc_channels);
	indio_dev->available_scan_masks = ssp_accel_scan_mask;

	buffer = devm_iio_kfifo_allocate(&pdev->dev);
	if (!buffer)
		return -ENOMEM;

	iio_device_attach_buffer(indio_dev, buffer);

	indio_dev->setup_ops = &ssp_accel_buffer_ops;

	platform_set_drvdata(pdev, indio_dev);

	ret = devm_iio_device_register(&pdev->dev, indio_dev);
	if (ret < 0)
		return ret;

	/* ssp registering should be done after all iio setup */
	ssp_register_consumer(indio_dev, SSP_ACCELEROMETER_SENSOR);

	return 0;
}