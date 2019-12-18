#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ti_dac_spec {int /*<<< orphan*/  resolution; int /*<<< orphan*/  num_channels; } ;
struct TYPE_6__ {struct spi_device* spi; } ;
struct TYPE_7__ {int len; int /*<<< orphan*/ * tx_buf; } ;
struct ti_dac_chip {int /*<<< orphan*/  vref; int /*<<< orphan*/  lock; int /*<<< orphan*/  resolution; TYPE_2__ mesg; TYPE_3__ xfer; int /*<<< orphan*/  buf; } ;
struct device {int dummy; } ;
struct spi_device {int /*<<< orphan*/  modalias; struct device dev; } ;
struct TYPE_5__ {struct device* parent; } ;
struct iio_dev {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/  name; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct TYPE_8__ {size_t driver_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ALL_UPDATE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int /*<<< orphan*/  devm_regulator_get (struct device*,char*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct ti_dac_chip* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 TYPE_4__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_message_init_with_transfers (TYPE_2__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 
 int /*<<< orphan*/  ti_dac_channels ; 
 int ti_dac_cmd (struct ti_dac_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_dac_info ; 
 struct ti_dac_spec* ti_dac_spec ; 

__attribute__((used)) static int ti_dac_probe(struct spi_device *spi)
{
	struct device *dev = &spi->dev;
	const struct ti_dac_spec *spec;
	struct ti_dac_chip *ti_dac;
	struct iio_dev *indio_dev;
	int ret;

	indio_dev = devm_iio_device_alloc(dev, sizeof(*ti_dac));
	if (!indio_dev)
		return -ENOMEM;

	indio_dev->dev.parent = dev;
	indio_dev->info = &ti_dac_info;
	indio_dev->name = spi->modalias;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = ti_dac_channels;
	spi_set_drvdata(spi, indio_dev);

	ti_dac = iio_priv(indio_dev);
	ti_dac->xfer.tx_buf = &ti_dac->buf;
	ti_dac->xfer.len = sizeof(ti_dac->buf);
	spi_message_init_with_transfers(&ti_dac->mesg, &ti_dac->xfer, 1);
	ti_dac->mesg.spi = spi;

	spec = &ti_dac_spec[spi_get_device_id(spi)->driver_data];
	indio_dev->num_channels = spec->num_channels;
	ti_dac->resolution = spec->resolution;

	ti_dac->vref = devm_regulator_get(dev, "vref");
	if (IS_ERR(ti_dac->vref))
		return PTR_ERR(ti_dac->vref);

	ret = regulator_enable(ti_dac->vref);
	if (ret < 0)
		return ret;

	mutex_init(&ti_dac->lock);

	ret = ti_dac_cmd(ti_dac, WRITE_ALL_UPDATE, 0);
	if (ret) {
		dev_err(dev, "failed to initialize outputs to 0\n");
		goto err;
	}

	ret = iio_device_register(indio_dev);
	if (ret)
		goto err;

	return 0;

err:
	mutex_destroy(&ti_dac->lock);
	regulator_disable(ti_dac->vref);
	return ret;
}