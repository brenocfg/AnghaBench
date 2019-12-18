#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  of_node; } ;
struct spi_device {TYPE_6__ dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  of_node; TYPE_6__* parent; } ;
struct iio_dev {int num_channels; int /*<<< orphan*/ * info; TYPE_3__* channels; int /*<<< orphan*/  modes; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct TYPE_12__ {int len; int /*<<< orphan*/ * rx_buf; } ;
struct ad7476_state {int /*<<< orphan*/  reg; TYPE_8__* chip_info; int /*<<< orphan*/  msg; TYPE_4__ xfer; int /*<<< orphan*/  data; struct spi_device* spi; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* reset ) (struct ad7476_state*) ;TYPE_3__* channel; } ;
struct TYPE_13__ {size_t driver_data; int /*<<< orphan*/  name; } ;
struct TYPE_10__ {int storagebits; } ;
struct TYPE_11__ {TYPE_2__ scan_type; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 TYPE_8__* ad7476_chip_info_tbl ; 
 int /*<<< orphan*/  ad7476_info ; 
 int /*<<< orphan*/  ad7476_trigger_handler ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_6__*,int) ; 
 int /*<<< orphan*/  devm_regulator_get (TYPE_6__*,char*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct ad7476_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int iio_triggered_buffer_setup (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 TYPE_5__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_message_add_tail (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 
 int /*<<< orphan*/  stub1 (struct ad7476_state*) ; 

__attribute__((used)) static int ad7476_probe(struct spi_device *spi)
{
	struct ad7476_state *st;
	struct iio_dev *indio_dev;
	int ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		return -ENOMEM;

	st = iio_priv(indio_dev);
	st->chip_info =
		&ad7476_chip_info_tbl[spi_get_device_id(spi)->driver_data];

	st->reg = devm_regulator_get(&spi->dev, "vcc");
	if (IS_ERR(st->reg))
		return PTR_ERR(st->reg);

	ret = regulator_enable(st->reg);
	if (ret)
		return ret;

	spi_set_drvdata(spi, indio_dev);

	st->spi = spi;

	/* Establish that the iio_dev is a child of the spi device */
	indio_dev->dev.parent = &spi->dev;
	indio_dev->dev.of_node = spi->dev.of_node;
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = st->chip_info->channel;
	indio_dev->num_channels = 2;
	indio_dev->info = &ad7476_info;
	/* Setup default message */

	st->xfer.rx_buf = &st->data;
	st->xfer.len = st->chip_info->channel[0].scan_type.storagebits / 8;

	spi_message_init(&st->msg);
	spi_message_add_tail(&st->xfer, &st->msg);

	ret = iio_triggered_buffer_setup(indio_dev, NULL,
			&ad7476_trigger_handler, NULL);
	if (ret)
		goto error_disable_reg;

	if (st->chip_info->reset)
		st->chip_info->reset(st);

	ret = iio_device_register(indio_dev);
	if (ret)
		goto error_ring_unregister;
	return 0;

error_ring_unregister:
	iio_triggered_buffer_cleanup(indio_dev);
error_disable_reg:
	regulator_disable(st->reg);

	return ret;
}