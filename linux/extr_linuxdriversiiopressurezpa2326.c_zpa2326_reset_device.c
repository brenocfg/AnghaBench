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
struct zpa2326_private {int /*<<< orphan*/  regmap; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZPA2326_CTRL_REG2_REG ; 
 int /*<<< orphan*/  ZPA2326_CTRL_REG2_SWRESET ; 
 int /*<<< orphan*/  ZPA2326_TPUP_USEC_MAX ; 
 int /*<<< orphan*/  ZPA2326_TPUP_USEC_MIN ; 
 scalar_t__ iio_priv (struct iio_dev const*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpa2326_dbg (struct iio_dev const*,char*) ; 
 int /*<<< orphan*/  zpa2326_err (struct iio_dev const*,char*,int) ; 

__attribute__((used)) static int zpa2326_reset_device(const struct iio_dev *indio_dev)
{
	int err;

	err = regmap_write(((struct zpa2326_private *)
			    iio_priv(indio_dev))->regmap,
			    ZPA2326_CTRL_REG2_REG, ZPA2326_CTRL_REG2_SWRESET);
	if (err) {
		zpa2326_err(indio_dev, "failed to reset device (%d)", err);
		return err;
	}

	usleep_range(ZPA2326_TPUP_USEC_MIN, ZPA2326_TPUP_USEC_MAX);

	zpa2326_dbg(indio_dev, "reset");

	return 0;
}