#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct iio_dev {int dummy; } ;
struct TYPE_14__ {TYPE_4__* spi; } ;
struct ad7793_state {int conf; int** scale_avail; TYPE_5__ sd; TYPE_3__* chip_info; int /*<<< orphan*/  mode; } ;
struct ad7793_platform_data {int exitation_current; int current_source_direction; scalar_t__ unipolar; scalar_t__ burnout_current; scalar_t__ boost_enable; scalar_t__ buffered; int /*<<< orphan*/  bias_voltage; int /*<<< orphan*/  refsel; int /*<<< orphan*/  clock_src; } ;
struct TYPE_13__ {int /*<<< orphan*/  dev; } ;
struct TYPE_12__ {int flags; TYPE_2__* channels; int /*<<< orphan*/  id; } ;
struct TYPE_10__ {int realbits; } ;
struct TYPE_11__ {TYPE_1__ scan_type; } ;

/* Variables and functions */
 int AD7793_CONF_BOOST ; 
 int AD7793_CONF_BO_EN ; 
 int AD7793_CONF_BUF ; 
 int AD7793_CONF_GAIN (int) ; 
 int AD7793_CONF_REFSEL (int /*<<< orphan*/ ) ; 
 int AD7793_CONF_UNIPOLAR ; 
 int AD7793_CONF_VBIAS (int /*<<< orphan*/ ) ; 
 int AD7793_FLAG_HAS_BUFFER ; 
 int AD7793_FLAG_HAS_CLKSEL ; 
 int AD7793_FLAG_HAS_GAIN ; 
 int AD7793_FLAG_HAS_REFSEL ; 
 int AD7793_FLAG_HAS_VBIAS ; 
 int AD7793_HAS_EXITATION_CURRENT ; 
 int /*<<< orphan*/  AD7793_ID_MASK ; 
 int /*<<< orphan*/  AD7793_MODE_CLKSRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AD7793_MODE_RATE (int) ; 
 int /*<<< orphan*/  AD7793_REG_ID ; 
 int /*<<< orphan*/  AD7793_REG_IO ; 
 int /*<<< orphan*/  AD_SD_MODE_IDLE ; 
 int ARRAY_SIZE (int**) ; 
 int ad7793_calibrate_all (struct ad7793_state*) ; 
 int ad7793_check_platform_data (struct ad7793_state*,struct ad7793_platform_data const*) ; 
 int ad7793_set_channel (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int ad7793_set_mode (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int ad_sd_read_reg (TYPE_5__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int ad_sd_reset (TYPE_5__*,int) ; 
 int ad_sd_write_reg (TYPE_5__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int do_div (unsigned long long,int) ; 
 struct ad7793_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ad7793_setup(struct iio_dev *indio_dev,
	const struct ad7793_platform_data *pdata,
	unsigned int vref_mv)
{
	struct ad7793_state *st = iio_priv(indio_dev);
	int i, ret;
	unsigned long long scale_uv;
	u32 id;

	ret = ad7793_check_platform_data(st, pdata);
	if (ret)
		return ret;

	/* reset the serial interface */
	ret = ad_sd_reset(&st->sd, 32);
	if (ret < 0)
		goto out;
	usleep_range(500, 2000); /* Wait for at least 500us */

	/* write/read test for device presence */
	ret = ad_sd_read_reg(&st->sd, AD7793_REG_ID, 1, &id);
	if (ret)
		goto out;

	id &= AD7793_ID_MASK;

	if (id != st->chip_info->id) {
		dev_err(&st->sd.spi->dev, "device ID query failed\n");
		goto out;
	}

	st->mode = AD7793_MODE_RATE(1);
	st->conf = 0;

	if (st->chip_info->flags & AD7793_FLAG_HAS_CLKSEL)
		st->mode |= AD7793_MODE_CLKSRC(pdata->clock_src);
	if (st->chip_info->flags & AD7793_FLAG_HAS_REFSEL)
		st->conf |= AD7793_CONF_REFSEL(pdata->refsel);
	if (st->chip_info->flags & AD7793_FLAG_HAS_VBIAS)
		st->conf |= AD7793_CONF_VBIAS(pdata->bias_voltage);
	if (pdata->buffered || !(st->chip_info->flags & AD7793_FLAG_HAS_BUFFER))
		st->conf |= AD7793_CONF_BUF;
	if (pdata->boost_enable &&
		(st->chip_info->flags & AD7793_FLAG_HAS_VBIAS))
		st->conf |= AD7793_CONF_BOOST;
	if (pdata->burnout_current)
		st->conf |= AD7793_CONF_BO_EN;
	if (pdata->unipolar)
		st->conf |= AD7793_CONF_UNIPOLAR;

	if (!(st->chip_info->flags & AD7793_FLAG_HAS_GAIN))
		st->conf |= AD7793_CONF_GAIN(7);

	ret = ad7793_set_mode(&st->sd, AD_SD_MODE_IDLE);
	if (ret)
		goto out;

	ret = ad7793_set_channel(&st->sd, 0);
	if (ret)
		goto out;

	if (st->chip_info->flags & AD7793_HAS_EXITATION_CURRENT) {
		ret = ad_sd_write_reg(&st->sd, AD7793_REG_IO, 1,
				pdata->exitation_current |
				(pdata->current_source_direction << 2));
		if (ret)
			goto out;
	}

	ret = ad7793_calibrate_all(st);
	if (ret)
		goto out;

	/* Populate available ADC input ranges */
	for (i = 0; i < ARRAY_SIZE(st->scale_avail); i++) {
		scale_uv = ((u64)vref_mv * 100000000)
			>> (st->chip_info->channels[0].scan_type.realbits -
			(!!(st->conf & AD7793_CONF_UNIPOLAR) ? 0 : 1));
		scale_uv >>= i;

		st->scale_avail[i][1] = do_div(scale_uv, 100000000) * 10;
		st->scale_avail[i][0] = scale_uv;
	}

	return 0;
out:
	dev_err(&st->sd.spi->dev, "setup failed\n");
	return ret;
}