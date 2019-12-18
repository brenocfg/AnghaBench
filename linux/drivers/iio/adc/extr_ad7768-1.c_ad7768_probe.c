#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct spi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct TYPE_8__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int modes; int /*<<< orphan*/  name; int /*<<< orphan*/  trig; int /*<<< orphan*/  id; int /*<<< orphan*/ * info; TYPE_1__ dev; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; } ;
struct ad7768_state {int /*<<< orphan*/  completion; TYPE_4__* trig; int /*<<< orphan*/  lock; int /*<<< orphan*/  mclk; int /*<<< orphan*/  mclk_freq; int /*<<< orphan*/  vref; struct spi_device* spi; } ;
struct TYPE_9__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_11__ {TYPE_2__ dev; int /*<<< orphan*/ * ops; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int INDIO_BUFFER_TRIGGERED ; 
 int INDIO_DIRECT_MODE ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ad7768_buffer_ops ; 
 int /*<<< orphan*/  ad7768_channels ; 
 int /*<<< orphan*/  ad7768_clk_disable ; 
 int /*<<< orphan*/  ad7768_info ; 
 int /*<<< orphan*/  ad7768_interrupt ; 
 int /*<<< orphan*/  ad7768_regulator_disable ; 
 int ad7768_setup (struct ad7768_state*) ; 
 int /*<<< orphan*/  ad7768_trigger_handler ; 
 int /*<<< orphan*/  ad7768_trigger_ops ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int devm_add_action_or_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ad7768_state*) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int devm_iio_device_register (int /*<<< orphan*/ *,struct iio_dev*) ; 
 TYPE_4__* devm_iio_trigger_alloc (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_iio_trigger_register (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int devm_iio_triggered_buffer_setup (int /*<<< orphan*/ *,struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct iio_dev*) ; 
 int /*<<< orphan*/  iio_pollfunc_store_time ; 
 struct ad7768_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_get (TYPE_4__*) ; 
 int /*<<< orphan*/  iio_trigger_set_drvdata (TYPE_4__*,struct iio_dev*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 TYPE_3__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 

__attribute__((used)) static int ad7768_probe(struct spi_device *spi)
{
	struct ad7768_state *st;
	struct iio_dev *indio_dev;
	int ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		return -ENOMEM;

	st = iio_priv(indio_dev);
	st->spi = spi;

	st->vref = devm_regulator_get(&spi->dev, "vref");
	if (IS_ERR(st->vref))
		return PTR_ERR(st->vref);

	ret = regulator_enable(st->vref);
	if (ret) {
		dev_err(&spi->dev, "Failed to enable specified vref supply\n");
		return ret;
	}

	ret = devm_add_action_or_reset(&spi->dev, ad7768_regulator_disable, st);
	if (ret)
		return ret;

	st->mclk = devm_clk_get(&spi->dev, "mclk");
	if (IS_ERR(st->mclk))
		return PTR_ERR(st->mclk);

	ret = clk_prepare_enable(st->mclk);
	if (ret < 0)
		return ret;

	ret = devm_add_action_or_reset(&spi->dev, ad7768_clk_disable, st);
	if (ret)
		return ret;

	st->mclk_freq = clk_get_rate(st->mclk);

	spi_set_drvdata(spi, indio_dev);
	mutex_init(&st->lock);

	indio_dev->channels = ad7768_channels;
	indio_dev->num_channels = ARRAY_SIZE(ad7768_channels);
	indio_dev->dev.parent = &spi->dev;
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->info = &ad7768_info;
	indio_dev->modes = INDIO_DIRECT_MODE | INDIO_BUFFER_TRIGGERED;

	ret = ad7768_setup(st);
	if (ret < 0) {
		dev_err(&spi->dev, "AD7768 setup failed\n");
		return ret;
	}

	st->trig = devm_iio_trigger_alloc(&spi->dev, "%s-dev%d",
					  indio_dev->name, indio_dev->id);
	if (!st->trig)
		return -ENOMEM;

	st->trig->ops = &ad7768_trigger_ops;
	st->trig->dev.parent = &spi->dev;
	iio_trigger_set_drvdata(st->trig, indio_dev);
	ret = devm_iio_trigger_register(&spi->dev, st->trig);
	if (ret)
		return ret;

	indio_dev->trig = iio_trigger_get(st->trig);

	init_completion(&st->completion);

	ret = devm_request_irq(&spi->dev, spi->irq,
			       &ad7768_interrupt,
			       IRQF_TRIGGER_RISING | IRQF_ONESHOT,
			       indio_dev->name, indio_dev);
	if (ret)
		return ret;

	ret = devm_iio_triggered_buffer_setup(&spi->dev, indio_dev,
					      &iio_pollfunc_store_time,
					      &ad7768_trigger_handler,
					      &ad7768_buffer_ops);
	if (ret)
		return ret;

	return devm_iio_device_register(&spi->dev, indio_dev);
}