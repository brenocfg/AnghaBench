#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  of_node; struct ad7266_platform_data* platform_data; } ;
struct spi_device {TYPE_7__ dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  of_node; TYPE_7__* parent; } ;
struct iio_dev {int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct TYPE_11__ {int /*<<< orphan*/ * sample; } ;
struct ad7266_state {int vref_mv; int fixed_addr; int /*<<< orphan*/  reg; TYPE_5__* gpios; int /*<<< orphan*/  single_msg; TYPE_3__* single_xfer; TYPE_2__ data; struct spi_device* spi; int /*<<< orphan*/  mode; int /*<<< orphan*/  range; } ;
struct ad7266_platform_data {int fixed_addr; int /*<<< orphan*/ * addr_gpios; int /*<<< orphan*/  range; int /*<<< orphan*/  mode; } ;
struct TYPE_14__ {int /*<<< orphan*/  label; int /*<<< orphan*/  flags; int /*<<< orphan*/  gpio; } ;
struct TYPE_13__ {int /*<<< orphan*/  name; } ;
struct TYPE_12__ {int len; int cs_change; int /*<<< orphan*/ * tx_buf; int /*<<< orphan*/ * rx_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD7266_MODE_DIFF ; 
 int /*<<< orphan*/  AD7266_RANGE_VREF ; 
 unsigned int ARRAY_SIZE (TYPE_5__*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_LOW ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ad7266_gpio_labels ; 
 int /*<<< orphan*/  ad7266_info ; 
 int /*<<< orphan*/  ad7266_init_channels (struct iio_dev*) ; 
 int /*<<< orphan*/  ad7266_trigger_handler ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_7__*,int) ; 
 int /*<<< orphan*/  devm_regulator_get_optional (TYPE_7__*,char*) ; 
 int /*<<< orphan*/  gpio_free_array (TYPE_5__*,unsigned int) ; 
 int gpio_request_array (TYPE_5__*,unsigned int) ; 
 int iio_device_register (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_pollfunc_store_time ; 
 struct ad7266_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int iio_triggered_buffer_setup (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_triggered_buffer_setup_ops ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int regulator_get_voltage (int /*<<< orphan*/ ) ; 
 TYPE_4__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_message_add_tail (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 

__attribute__((used)) static int ad7266_probe(struct spi_device *spi)
{
	struct ad7266_platform_data *pdata = spi->dev.platform_data;
	struct iio_dev *indio_dev;
	struct ad7266_state *st;
	unsigned int i;
	int ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*st));
	if (indio_dev == NULL)
		return -ENOMEM;

	st = iio_priv(indio_dev);

	st->reg = devm_regulator_get_optional(&spi->dev, "vref");
	if (!IS_ERR(st->reg)) {
		ret = regulator_enable(st->reg);
		if (ret)
			return ret;

		ret = regulator_get_voltage(st->reg);
		if (ret < 0)
			goto error_disable_reg;

		st->vref_mv = ret / 1000;
	} else {
		/* Any other error indicates that the regulator does exist */
		if (PTR_ERR(st->reg) != -ENODEV)
			return PTR_ERR(st->reg);
		/* Use internal reference */
		st->vref_mv = 2500;
	}

	if (pdata) {
		st->fixed_addr = pdata->fixed_addr;
		st->mode = pdata->mode;
		st->range = pdata->range;

		if (!st->fixed_addr) {
			for (i = 0; i < ARRAY_SIZE(st->gpios); ++i) {
				st->gpios[i].gpio = pdata->addr_gpios[i];
				st->gpios[i].flags = GPIOF_OUT_INIT_LOW;
				st->gpios[i].label = ad7266_gpio_labels[i];
			}
			ret = gpio_request_array(st->gpios,
				ARRAY_SIZE(st->gpios));
			if (ret)
				goto error_disable_reg;
		}
	} else {
		st->fixed_addr = true;
		st->range = AD7266_RANGE_VREF;
		st->mode = AD7266_MODE_DIFF;
	}

	spi_set_drvdata(spi, indio_dev);
	st->spi = spi;

	indio_dev->dev.parent = &spi->dev;
	indio_dev->dev.of_node = spi->dev.of_node;
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->info = &ad7266_info;

	ad7266_init_channels(indio_dev);

	/* wakeup */
	st->single_xfer[0].rx_buf = &st->data.sample[0];
	st->single_xfer[0].len = 2;
	st->single_xfer[0].cs_change = 1;
	/* conversion */
	st->single_xfer[1].rx_buf = st->data.sample;
	st->single_xfer[1].len = 4;
	st->single_xfer[1].cs_change = 1;
	/* powerdown */
	st->single_xfer[2].tx_buf = &st->data.sample[0];
	st->single_xfer[2].len = 1;

	spi_message_init(&st->single_msg);
	spi_message_add_tail(&st->single_xfer[0], &st->single_msg);
	spi_message_add_tail(&st->single_xfer[1], &st->single_msg);
	spi_message_add_tail(&st->single_xfer[2], &st->single_msg);

	ret = iio_triggered_buffer_setup(indio_dev, &iio_pollfunc_store_time,
		&ad7266_trigger_handler, &iio_triggered_buffer_setup_ops);
	if (ret)
		goto error_free_gpios;

	ret = iio_device_register(indio_dev);
	if (ret)
		goto error_buffer_cleanup;

	return 0;

error_buffer_cleanup:
	iio_triggered_buffer_cleanup(indio_dev);
error_free_gpios:
	if (!st->fixed_addr)
		gpio_free_array(st->gpios, ARRAY_SIZE(st->gpios));
error_disable_reg:
	if (!IS_ERR(st->reg))
		regulator_disable(st->reg);

	return ret;
}