#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  address; } ;
struct adxl345_data {int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int /*<<< orphan*/  ADXL345_BASE_RATE_NANO_HZ ; 
 int /*<<< orphan*/  ADXL345_BW_RATE ; 
 int /*<<< orphan*/  ADXL345_REG_BW_RATE ; 
 int /*<<< orphan*/  ADXL345_REG_OFS_AXIS (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_CALIBBIAS 129 
#define  IIO_CHAN_INFO_SAMP_FREQ 128 
 int NHZ_PER_HZ ; 
 int /*<<< orphan*/  clamp_val (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  div_s64 (int,int /*<<< orphan*/ ) ; 
 struct adxl345_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  ilog2 (int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int adxl345_write_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int val, int val2, long mask)
{
	struct adxl345_data *data = iio_priv(indio_dev);
	s64 n;

	switch (mask) {
	case IIO_CHAN_INFO_CALIBBIAS:
		/*
		 * 8-bit resolution at +/- 2g, that is 4x accel data scale
		 * factor
		 */
		return regmap_write(data->regmap,
				    ADXL345_REG_OFS_AXIS(chan->address),
				    val / 4);
	case IIO_CHAN_INFO_SAMP_FREQ:
		n = div_s64(val * NHZ_PER_HZ + val2, ADXL345_BASE_RATE_NANO_HZ);

		return regmap_update_bits(data->regmap, ADXL345_REG_BW_RATE,
					  ADXL345_BW_RATE,
					  clamp_val(ilog2(n), 0,
						    ADXL345_BW_RATE));
	}

	return -EINVAL;
}