#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct itg3200 {TYPE_1__* i2c; } ;
struct iio_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  ITG3200_REG_ADDRESS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct itg3200* iio_priv (struct iio_dev*) ; 
 int itg3200_enable_full_scale (struct iio_dev*) ; 
 int itg3200_read_reg_8 (struct iio_dev*,int /*<<< orphan*/ ,int*) ; 
 int itg3200_reset (struct iio_dev*) ; 

__attribute__((used)) static int itg3200_initial_setup(struct iio_dev *indio_dev)
{
	struct itg3200 *st = iio_priv(indio_dev);
	int ret;
	u8 val;

	ret = itg3200_reset(indio_dev);
	if (ret)
		goto err_ret;

	ret = itg3200_read_reg_8(indio_dev, ITG3200_REG_ADDRESS, &val);
	if (ret)
		goto err_ret;

	if (((val >> 1) & 0x3f) != 0x34) {
		dev_err(&st->i2c->dev, "invalid reg value 0x%02x", val);
		ret = -ENXIO;
		goto err_ret;
	}

	ret = itg3200_enable_full_scale(indio_dev);
err_ret:
	return ret;
}