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
typedef  int u8 ;
struct zpa2326_private {struct regmap* regmap; } ;
struct regmap {int dummy; } ;
struct iio_dev {int dummy; } ;
typedef  enum iio_chan_type { ____Placeholder_iio_chan_type } iio_chan_type ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_PRESSURE 129 
#define  IIO_TEMP 128 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  ZPA2326_PRESS_OUT_XL_REG ; 
 int /*<<< orphan*/  ZPA2326_TEMP_OUT_L_REG ; 
 scalar_t__ iio_priv (struct iio_dev const*) ; 
 scalar_t__ le16_to_cpup (int /*<<< orphan*/ *) ; 
 int regmap_bulk_read (struct regmap*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  zpa2326_dbg (struct iio_dev const*,char*) ; 
 int /*<<< orphan*/  zpa2326_warn (struct iio_dev const*,char*,int) ; 

__attribute__((used)) static int zpa2326_fetch_raw_sample(const struct iio_dev *indio_dev,
				    enum iio_chan_type    type,
				    int                  *value)
{
	struct regmap *regs = ((struct zpa2326_private *)
			       iio_priv(indio_dev))->regmap;
	int            err;

	switch (type) {
	case IIO_PRESSURE:
		zpa2326_dbg(indio_dev, "fetching raw pressure sample");

		err = regmap_bulk_read(regs, ZPA2326_PRESS_OUT_XL_REG, value,
				       3);
		if (err) {
			zpa2326_warn(indio_dev, "failed to fetch pressure (%d)",
				     err);
			return err;
		}

		/* Pressure is a 24 bits wide little-endian unsigned int. */
		*value = (((u8 *)value)[2] << 16) | (((u8 *)value)[1] << 8) |
			 ((u8 *)value)[0];

		return IIO_VAL_INT;

	case IIO_TEMP:
		zpa2326_dbg(indio_dev, "fetching raw temperature sample");

		err = regmap_bulk_read(regs, ZPA2326_TEMP_OUT_L_REG, value, 2);
		if (err) {
			zpa2326_warn(indio_dev,
				     "failed to fetch temperature (%d)", err);
			return err;
		}

		/* Temperature is a 16 bits wide little-endian signed int. */
		*value = (int)le16_to_cpup((__le16 *)value);

		return IIO_VAL_INT;

	default:
		return -EINVAL;
	}
}