#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct iio_dev {TYPE_2__* channels; } ;
struct device_node {int dummy; } ;
struct TYPE_10__ {TYPE_3__* spi; } ;
struct ad7192_state {int devid; int mode; int conf; int** scale_avail; scalar_t__ int_vref_mv; TYPE_4__ sd; int /*<<< orphan*/  f_order; int /*<<< orphan*/  clock_sel; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int realbits; } ;
struct TYPE_8__ {TYPE_1__ scan_type; } ;

/* Variables and functions */
 int AD7192_CONF_BUF ; 
 int AD7192_CONF_BURN ; 
 int AD7192_CONF_CHOP ; 
 int AD7192_CONF_GAIN (int /*<<< orphan*/ ) ; 
 int AD7192_CONF_REFSEL ; 
 int AD7192_CONF_UNIPOLAR ; 
 int AD7192_ID_MASK ; 
 int AD7192_MODE_CLKSRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AD7192_MODE_IDLE ; 
 int AD7192_MODE_RATE (int) ; 
 int AD7192_MODE_REJ60 ; 
 int AD7192_MODE_SEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AD7192_NO_SYNC_FILTER ; 
 int /*<<< orphan*/  AD7192_REG_CONF ; 
 int /*<<< orphan*/  AD7192_REG_ID ; 
 int /*<<< orphan*/  AD7192_REG_MODE ; 
 int ARRAY_SIZE (int**) ; 
 int ID_AD7195 ; 
 int ad7192_calibrate_all (struct ad7192_state*) ; 
 int ad_sd_read_reg (TYPE_4__*,int /*<<< orphan*/ ,int,int*) ; 
 int ad_sd_reset (TYPE_4__*,int) ; 
 int ad_sd_write_reg (TYPE_4__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 int do_div (unsigned long long,int) ; 
 int of_property_read_bool (struct device_node*,char*) ; 
 struct iio_dev* spi_get_drvdata (TYPE_3__*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ad7192_setup(struct ad7192_state *st, struct device_node *np)
{
	struct iio_dev *indio_dev = spi_get_drvdata(st->sd.spi);
	bool rej60_en, refin2_en;
	bool buf_en, bipolar, burnout_curr_en;
	unsigned long long scale_uv;
	int i, ret, id;

	/* reset the serial interface */
	ret = ad_sd_reset(&st->sd, 48);
	if (ret < 0)
		return ret;
	usleep_range(500, 1000); /* Wait for at least 500us */

	/* write/read test for device presence */
	ret = ad_sd_read_reg(&st->sd, AD7192_REG_ID, 1, &id);
	if (ret)
		return ret;

	id &= AD7192_ID_MASK;

	if (id != st->devid)
		dev_warn(&st->sd.spi->dev, "device ID query failed (0x%X)\n",
			 id);

	st->mode = AD7192_MODE_SEL(AD7192_MODE_IDLE) |
		AD7192_MODE_CLKSRC(st->clock_sel) |
		AD7192_MODE_RATE(480);

	st->conf = AD7192_CONF_GAIN(0);

	rej60_en = of_property_read_bool(np, "adi,rejection-60-Hz-enable");
	if (rej60_en)
		st->mode |= AD7192_MODE_REJ60;

	refin2_en = of_property_read_bool(np, "adi,refin2-pins-enable");
	if (refin2_en && st->devid != ID_AD7195)
		st->conf |= AD7192_CONF_REFSEL;

	st->conf &= ~AD7192_CONF_CHOP;
	st->f_order = AD7192_NO_SYNC_FILTER;

	buf_en = of_property_read_bool(np, "adi,buffer-enable");
	if (buf_en)
		st->conf |= AD7192_CONF_BUF;

	bipolar = of_property_read_bool(np, "bipolar");
	if (!bipolar)
		st->conf |= AD7192_CONF_UNIPOLAR;

	burnout_curr_en = of_property_read_bool(np,
						"adi,burnout-currents-enable");
	if (burnout_curr_en && buf_en) {
		st->conf |= AD7192_CONF_BURN;
	} else if (burnout_curr_en) {
		dev_warn(&st->sd.spi->dev,
			 "Can't enable burnout currents: see CHOP or buffer\n");
	}

	ret = ad_sd_write_reg(&st->sd, AD7192_REG_MODE, 3, st->mode);
	if (ret)
		return ret;

	ret = ad_sd_write_reg(&st->sd, AD7192_REG_CONF, 3, st->conf);
	if (ret)
		return ret;

	ret = ad7192_calibrate_all(st);
	if (ret)
		return ret;

	/* Populate available ADC input ranges */
	for (i = 0; i < ARRAY_SIZE(st->scale_avail); i++) {
		scale_uv = ((u64)st->int_vref_mv * 100000000)
			>> (indio_dev->channels[0].scan_type.realbits -
			((st->conf & AD7192_CONF_UNIPOLAR) ? 0 : 1));
		scale_uv >>= i;

		st->scale_avail[i][1] = do_div(scale_uv, 100000000) * 10;
		st->scale_avail[i][0] = scale_uv;
	}

	return 0;
}