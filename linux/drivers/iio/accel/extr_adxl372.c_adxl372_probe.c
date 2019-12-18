#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct TYPE_8__ {struct device* parent; } ;
struct iio_dev {char const* name; int modes; int /*<<< orphan*/  trig; int /*<<< orphan*/  id; int /*<<< orphan*/  buffer; int /*<<< orphan*/ * info; TYPE_1__ dev; int /*<<< orphan*/  available_scan_masks; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; } ;
struct device {int dummy; } ;
struct adxl372_state {int irq; TYPE_3__* dready_trig; struct regmap* regmap; struct device* dev; } ;
struct TYPE_9__ {struct device* parent; } ;
struct TYPE_10__ {TYPE_2__ dev; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int INDIO_BUFFER_SOFTWARE ; 
 int INDIO_DIRECT_MODE ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  adxl372_buffer_ops ; 
 int /*<<< orphan*/  adxl372_channel_masks ; 
 int /*<<< orphan*/  adxl372_channels ; 
 int /*<<< orphan*/  adxl372_fifo_attributes ; 
 int /*<<< orphan*/  adxl372_info ; 
 int adxl372_setup (struct adxl372_state*) ; 
 int /*<<< orphan*/  adxl372_trigger_handler ; 
 int /*<<< orphan*/  adxl372_trigger_ops ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct iio_dev*) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int devm_iio_device_register (struct device*,struct iio_dev*) ; 
 TYPE_3__* devm_iio_trigger_alloc (struct device*,char*,char const*,int /*<<< orphan*/ ) ; 
 int devm_iio_trigger_register (struct device*,TYPE_3__*) ; 
 int devm_iio_triggered_buffer_setup (struct device*,struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char const*,TYPE_3__*) ; 
 int /*<<< orphan*/  iio_buffer_set_attrs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct adxl372_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_generic_data_rdy_poll ; 
 int /*<<< orphan*/  iio_trigger_get (TYPE_3__*) ; 
 int /*<<< orphan*/  iio_trigger_set_drvdata (TYPE_3__*,struct iio_dev*) ; 

int adxl372_probe(struct device *dev, struct regmap *regmap,
		  int irq, const char *name)
{
	struct iio_dev *indio_dev;
	struct adxl372_state *st;
	int ret;

	indio_dev = devm_iio_device_alloc(dev, sizeof(*st));
	if (!indio_dev)
		return -ENOMEM;

	st = iio_priv(indio_dev);
	dev_set_drvdata(dev, indio_dev);

	st->dev = dev;
	st->regmap = regmap;
	st->irq = irq;

	indio_dev->channels = adxl372_channels;
	indio_dev->num_channels = ARRAY_SIZE(adxl372_channels);
	indio_dev->available_scan_masks = adxl372_channel_masks;
	indio_dev->dev.parent = dev;
	indio_dev->name = name;
	indio_dev->info = &adxl372_info;
	indio_dev->modes = INDIO_DIRECT_MODE | INDIO_BUFFER_SOFTWARE;

	ret = adxl372_setup(st);
	if (ret < 0) {
		dev_err(dev, "ADXL372 setup failed\n");
		return ret;
	}

	ret = devm_iio_triggered_buffer_setup(dev,
					      indio_dev, NULL,
					      adxl372_trigger_handler,
					      &adxl372_buffer_ops);
	if (ret < 0)
		return ret;

	iio_buffer_set_attrs(indio_dev->buffer, adxl372_fifo_attributes);

	if (st->irq) {
		st->dready_trig = devm_iio_trigger_alloc(dev,
							 "%s-dev%d",
							 indio_dev->name,
							 indio_dev->id);
		if (st->dready_trig == NULL)
			return -ENOMEM;

		st->dready_trig->ops = &adxl372_trigger_ops;
		st->dready_trig->dev.parent = dev;
		iio_trigger_set_drvdata(st->dready_trig, indio_dev);
		ret = devm_iio_trigger_register(dev, st->dready_trig);
		if (ret < 0)
			return ret;

		indio_dev->trig = iio_trigger_get(st->dready_trig);

		ret = devm_request_threaded_irq(dev, st->irq,
					iio_trigger_generic_data_rdy_poll,
					NULL,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					indio_dev->name, st->dready_trig);
		if (ret < 0)
			return ret;
	}

	return devm_iio_device_register(dev, indio_dev);
}