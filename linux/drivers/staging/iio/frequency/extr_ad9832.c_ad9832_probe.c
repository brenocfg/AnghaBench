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
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct TYPE_5__ {int len; int cs_change; int /*<<< orphan*/ * tx_buf; } ;
struct ad9832_state {int ctrl_src; void* avdd; void* dvdd; void* mclk; int /*<<< orphan*/  msg; struct spi_device* spi; int /*<<< orphan*/  data; int /*<<< orphan*/  phase_msg; TYPE_2__* phase_xfer; int /*<<< orphan*/ * phase_data; int /*<<< orphan*/  freq_msg; TYPE_2__* freq_xfer; int /*<<< orphan*/ * freq_data; TYPE_2__ xfer; int /*<<< orphan*/  lock; } ;
struct ad9832_platform_data {int /*<<< orphan*/  phase3; int /*<<< orphan*/  phase2; int /*<<< orphan*/  phase1; int /*<<< orphan*/  phase0; int /*<<< orphan*/  freq1; int /*<<< orphan*/  freq0; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int AD9832_CLR ; 
 int AD9832_CMD_SLEEPRESCLR ; 
 int /*<<< orphan*/  AD9832_FREQ0HM ; 
 int /*<<< orphan*/  AD9832_FREQ1HM ; 
 int /*<<< orphan*/  AD9832_PHASE0H ; 
 int /*<<< orphan*/  AD9832_PHASE1H ; 
 int /*<<< orphan*/  AD9832_PHASE2H ; 
 int /*<<< orphan*/  AD9832_PHASE3H ; 
 int AD9832_RESET ; 
 int AD9832_SLEEP ; 
 int CMD_SHIFT ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  ad9832_info ; 
 int ad9832_write_frequency (struct ad9832_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ad9832_write_phase (struct ad9832_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct ad9832_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 void* devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 void* devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct ad9832_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (void*) ; 
 int regulator_enable (void*) ; 
 TYPE_3__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_message_add_tail (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 
 int spi_sync (struct spi_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad9832_probe(struct spi_device *spi)
{
	struct ad9832_platform_data *pdata = dev_get_platdata(&spi->dev);
	struct iio_dev *indio_dev;
	struct ad9832_state *st;
	int ret;

	if (!pdata) {
		dev_dbg(&spi->dev, "no platform data?\n");
		return -ENODEV;
	}

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		return -ENOMEM;

	spi_set_drvdata(spi, indio_dev);
	st = iio_priv(indio_dev);

	st->avdd = devm_regulator_get(&spi->dev, "avdd");
	if (IS_ERR(st->avdd))
		return PTR_ERR(st->avdd);

	ret = regulator_enable(st->avdd);
	if (ret) {
		dev_err(&spi->dev, "Failed to enable specified AVDD supply\n");
		return ret;
	}

	st->dvdd = devm_regulator_get(&spi->dev, "dvdd");
	if (IS_ERR(st->dvdd)) {
		ret = PTR_ERR(st->dvdd);
		goto error_disable_avdd;
	}

	ret = regulator_enable(st->dvdd);
	if (ret) {
		dev_err(&spi->dev, "Failed to enable specified DVDD supply\n");
		goto error_disable_avdd;
	}

	st->mclk = devm_clk_get(&spi->dev, "mclk");
	if (IS_ERR(st->mclk)) {
		ret = PTR_ERR(st->mclk);
		goto error_disable_dvdd;
	}

	ret = clk_prepare_enable(st->mclk);
	if (ret < 0)
		goto error_disable_dvdd;

	st->spi = spi;
	mutex_init(&st->lock);

	indio_dev->dev.parent = &spi->dev;
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->info = &ad9832_info;
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
	st->freq_xfer[1].cs_change = 1;
	st->freq_xfer[2].tx_buf = &st->freq_data[2];
	st->freq_xfer[2].len = 2;
	st->freq_xfer[2].cs_change = 1;
	st->freq_xfer[3].tx_buf = &st->freq_data[3];
	st->freq_xfer[3].len = 2;

	spi_message_init(&st->freq_msg);
	spi_message_add_tail(&st->freq_xfer[0], &st->freq_msg);
	spi_message_add_tail(&st->freq_xfer[1], &st->freq_msg);
	spi_message_add_tail(&st->freq_xfer[2], &st->freq_msg);
	spi_message_add_tail(&st->freq_xfer[3], &st->freq_msg);

	st->phase_xfer[0].tx_buf = &st->phase_data[0];
	st->phase_xfer[0].len = 2;
	st->phase_xfer[0].cs_change = 1;
	st->phase_xfer[1].tx_buf = &st->phase_data[1];
	st->phase_xfer[1].len = 2;

	spi_message_init(&st->phase_msg);
	spi_message_add_tail(&st->phase_xfer[0], &st->phase_msg);
	spi_message_add_tail(&st->phase_xfer[1], &st->phase_msg);

	st->ctrl_src = AD9832_SLEEP | AD9832_RESET | AD9832_CLR;
	st->data = cpu_to_be16((AD9832_CMD_SLEEPRESCLR << CMD_SHIFT) |
					st->ctrl_src);
	ret = spi_sync(st->spi, &st->msg);
	if (ret) {
		dev_err(&spi->dev, "device init failed\n");
		goto error_unprepare_mclk;
	}

	ret = ad9832_write_frequency(st, AD9832_FREQ0HM, pdata->freq0);
	if (ret)
		goto error_unprepare_mclk;

	ret = ad9832_write_frequency(st, AD9832_FREQ1HM, pdata->freq1);
	if (ret)
		goto error_unprepare_mclk;

	ret = ad9832_write_phase(st, AD9832_PHASE0H, pdata->phase0);
	if (ret)
		goto error_unprepare_mclk;

	ret = ad9832_write_phase(st, AD9832_PHASE1H, pdata->phase1);
	if (ret)
		goto error_unprepare_mclk;

	ret = ad9832_write_phase(st, AD9832_PHASE2H, pdata->phase2);
	if (ret)
		goto error_unprepare_mclk;

	ret = ad9832_write_phase(st, AD9832_PHASE3H, pdata->phase3);
	if (ret)
		goto error_unprepare_mclk;

	ret = iio_device_register(indio_dev);
	if (ret)
		goto error_unprepare_mclk;

	return 0;

error_unprepare_mclk:
	clk_disable_unprepare(st->mclk);
error_disable_dvdd:
	regulator_disable(st->dvdd);
error_disable_avdd:
	regulator_disable(st->avdd);

	return ret;
}