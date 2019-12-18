#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct spi_device {int /*<<< orphan*/  dev; } ;
struct regulator {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct TYPE_5__ {int len; int cs_change; int /*<<< orphan*/ * tx_buf; } ;
struct ad9834_state {int devid; int control; int /*<<< orphan*/  mclk; int /*<<< orphan*/  msg; struct spi_device* spi; int /*<<< orphan*/  data; int /*<<< orphan*/  freq_msg; TYPE_2__* freq_xfer; int /*<<< orphan*/ * freq_data; TYPE_2__ xfer; struct regulator* reg; int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {int driver_data; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int AD9834_B28 ; 
 int AD9834_DIV2 ; 
 int AD9834_REG_CMD ; 
 int /*<<< orphan*/  AD9834_REG_FREQ0 ; 
 int /*<<< orphan*/  AD9834_REG_FREQ1 ; 
 int /*<<< orphan*/  AD9834_REG_PHASE0 ; 
 int /*<<< orphan*/  AD9834_REG_PHASE1 ; 
 int AD9834_RESET ; 
 int AD9834_SIGN_PIB ; 
 int ENOMEM ; 
#define  ID_AD9833 129 
 int ID_AD9834 ; 
#define  ID_AD9837 128 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (struct regulator*) ; 
 int PTR_ERR (struct regulator*) ; 
 int /*<<< orphan*/  ad9833_info ; 
 int /*<<< orphan*/  ad9834_info ; 
 int ad9834_write_frequency (struct ad9834_state*,int /*<<< orphan*/ ,int) ; 
 int ad9834_write_phase (struct ad9834_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 struct regulator* devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct ad9834_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (struct regulator*) ; 
 int regulator_enable (struct regulator*) ; 
 TYPE_3__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_message_add_tail (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 
 int spi_sync (struct spi_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad9834_probe(struct spi_device *spi)
{
	struct ad9834_state *st;
	struct iio_dev *indio_dev;
	struct regulator *reg;
	int ret;


	reg = devm_regulator_get(&spi->dev, "avdd");
	if (IS_ERR(reg))
		return PTR_ERR(reg);

	ret = regulator_enable(reg);
	if (ret) {
		dev_err(&spi->dev, "Failed to enable specified AVDD supply\n");
		return ret;
	}

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*st));
	if (!indio_dev) {
		ret = -ENOMEM;
		goto error_disable_reg;
	}
	spi_set_drvdata(spi, indio_dev);
	st = iio_priv(indio_dev);
	mutex_init(&st->lock);
	st->mclk = devm_clk_get(&spi->dev, NULL);

	ret = clk_prepare_enable(st->mclk);
	if (ret) {
		dev_err(&spi->dev, "Failed to enable master clock\n");
		goto error_disable_reg;
	}

	st->spi = spi;
	st->devid = spi_get_device_id(spi)->driver_data;
	st->reg = reg;
	indio_dev->dev.parent = &spi->dev;
	indio_dev->name = spi_get_device_id(spi)->name;
	switch (st->devid) {
	case ID_AD9833:
	case ID_AD9837:
		indio_dev->info = &ad9833_info;
		break;
	default:
		indio_dev->info = &ad9834_info;
		break;
	}
	indio_dev->modes = INDIO_DIRECT_MODE;

	/* Setup default messages */

	st->xfer.tx_buf = &st->data;
	st->xfer.len = 2;

	spi_message_init(&st->msg);
	spi_message_add_tail(&st->xfer, &st->msg);

	st->freq_xfer[0].tx_buf = &st->freq_data[0];
	st->freq_xfer[0].len = 2;
	st->freq_xfer[0].cs_change = 1;
	st->freq_xfer[1].tx_buf = &st->freq_data[1];
	st->freq_xfer[1].len = 2;

	spi_message_init(&st->freq_msg);
	spi_message_add_tail(&st->freq_xfer[0], &st->freq_msg);
	spi_message_add_tail(&st->freq_xfer[1], &st->freq_msg);

	st->control = AD9834_B28 | AD9834_RESET;
	st->control |= AD9834_DIV2;

	if (st->devid == ID_AD9834)
		st->control |= AD9834_SIGN_PIB;

	st->data = cpu_to_be16(AD9834_REG_CMD | st->control);
	ret = spi_sync(st->spi, &st->msg);
	if (ret) {
		dev_err(&spi->dev, "device init failed\n");
		goto error_clock_unprepare;
	}

	ret = ad9834_write_frequency(st, AD9834_REG_FREQ0, 1000000);
	if (ret)
		goto error_clock_unprepare;

	ret = ad9834_write_frequency(st, AD9834_REG_FREQ1, 5000000);
	if (ret)
		goto error_clock_unprepare;

	ret = ad9834_write_phase(st, AD9834_REG_PHASE0, 512);
	if (ret)
		goto error_clock_unprepare;

	ret = ad9834_write_phase(st, AD9834_REG_PHASE1, 1024);
	if (ret)
		goto error_clock_unprepare;

	ret = iio_device_register(indio_dev);
	if (ret)
		goto error_clock_unprepare;

	return 0;
error_clock_unprepare:
	clk_disable_unprepare(st->mclk);
error_disable_reg:
	regulator_disable(reg);

	return ret;
}