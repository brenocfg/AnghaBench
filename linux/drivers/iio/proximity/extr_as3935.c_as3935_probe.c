#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {struct device_node* of_node; } ;
struct spi_device {TYPE_4__ dev; int /*<<< orphan*/  irq; } ;
struct TYPE_14__ {TYPE_4__* parent; } ;
struct iio_trigger {int /*<<< orphan*/ * ops; TYPE_1__ dev; } ;
struct TYPE_15__ {TYPE_4__* parent; } ;
struct iio_dev {TYPE_2__ dev; int /*<<< orphan*/  id; int /*<<< orphan*/  name; int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; } ;
struct device_node {int dummy; } ;
struct as3935_state {scalar_t__ tune_cap; scalar_t__ nflwdth_reg; int /*<<< orphan*/  work; scalar_t__ noise_tripped; struct iio_trigger* trig; int /*<<< orphan*/  lock; struct spi_device* spi; } ;
struct TYPE_16__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ AS3935_NFLWDTH_MASK ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_TRIGGER_RISING ; 
 scalar_t__ MAX_PF_CAP ; 
 int /*<<< orphan*/  as3935_channels ; 
 int /*<<< orphan*/  as3935_event_work ; 
 int /*<<< orphan*/  as3935_info ; 
 int /*<<< orphan*/  as3935_interrupt_handler ; 
 int /*<<< orphan*/  as3935_stop_work ; 
 int /*<<< orphan*/  as3935_trigger_handler ; 
 int /*<<< orphan*/  calibrate_as3935 (struct as3935_state*) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_4__*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_4__*,char*,scalar_t__) ; 
 int devm_add_action (TYPE_4__*,int /*<<< orphan*/ ,struct iio_dev*) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_4__*,int) ; 
 int devm_iio_device_register (TYPE_4__*,struct iio_dev*) ; 
 struct iio_trigger* devm_iio_trigger_alloc (TYPE_4__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_iio_trigger_register (TYPE_4__*,struct iio_trigger*) ; 
 int devm_iio_triggered_buffer_setup (TYPE_4__*,struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int devm_request_irq (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iio_dev*) ; 
 int /*<<< orphan*/  iio_interrupt_trigger_ops ; 
 int /*<<< orphan*/  iio_pollfunc_store_time ; 
 struct as3935_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_set_drvdata (struct iio_trigger*,struct iio_dev*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 
 TYPE_3__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 

__attribute__((used)) static int as3935_probe(struct spi_device *spi)
{
	struct iio_dev *indio_dev;
	struct iio_trigger *trig;
	struct as3935_state *st;
	struct device_node *np = spi->dev.of_node;
	int ret;

	/* Be sure lightning event interrupt is specified */
	if (!spi->irq) {
		dev_err(&spi->dev, "unable to get event interrupt\n");
		return -EINVAL;
	}

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		return -ENOMEM;

	st = iio_priv(indio_dev);
	st->spi = spi;

	spi_set_drvdata(spi, indio_dev);
	mutex_init(&st->lock);

	ret = of_property_read_u32(np,
			"ams,tuning-capacitor-pf", &st->tune_cap);
	if (ret) {
		st->tune_cap = 0;
		dev_warn(&spi->dev,
			"no tuning-capacitor-pf set, defaulting to %d",
			st->tune_cap);
	}

	if (st->tune_cap > MAX_PF_CAP) {
		dev_err(&spi->dev,
			"wrong tuning-capacitor-pf setting of %d\n",
			st->tune_cap);
		return -EINVAL;
	}

	ret = of_property_read_u32(np,
			"ams,nflwdth", &st->nflwdth_reg);
	if (!ret && st->nflwdth_reg > AS3935_NFLWDTH_MASK) {
		dev_err(&spi->dev,
			"invalid nflwdth setting of %d\n",
			st->nflwdth_reg);
		return -EINVAL;
	}

	indio_dev->dev.parent = &spi->dev;
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->channels = as3935_channels;
	indio_dev->num_channels = ARRAY_SIZE(as3935_channels);
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->info = &as3935_info;

	trig = devm_iio_trigger_alloc(&spi->dev, "%s-dev%d",
				      indio_dev->name, indio_dev->id);

	if (!trig)
		return -ENOMEM;

	st->trig = trig;
	st->noise_tripped = jiffies - HZ;
	trig->dev.parent = indio_dev->dev.parent;
	iio_trigger_set_drvdata(trig, indio_dev);
	trig->ops = &iio_interrupt_trigger_ops;

	ret = devm_iio_trigger_register(&spi->dev, trig);
	if (ret) {
		dev_err(&spi->dev, "failed to register trigger\n");
		return ret;
	}

	ret = devm_iio_triggered_buffer_setup(&spi->dev, indio_dev,
					      iio_pollfunc_store_time,
					      as3935_trigger_handler, NULL);

	if (ret) {
		dev_err(&spi->dev, "cannot setup iio trigger\n");
		return ret;
	}

	calibrate_as3935(st);

	INIT_DELAYED_WORK(&st->work, as3935_event_work);
	ret = devm_add_action(&spi->dev, as3935_stop_work, indio_dev);
	if (ret)
		return ret;

	ret = devm_request_irq(&spi->dev, spi->irq,
				&as3935_interrupt_handler,
				IRQF_TRIGGER_RISING,
				dev_name(&spi->dev),
				indio_dev);

	if (ret) {
		dev_err(&spi->dev, "unable to request irq\n");
		return ret;
	}

	ret = devm_iio_device_register(&spi->dev, indio_dev);
	if (ret < 0) {
		dev_err(&spi->dev, "unable to register device\n");
		return ret;
	}
	return 0;
}