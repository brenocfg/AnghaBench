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
struct iio_dev {int /*<<< orphan*/  dev; } ;
struct adis16480 {int /*<<< orphan*/  adis; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADIS16480_REG_SLP_CNT ; 
 int /*<<< orphan*/  BIT (int) ; 
 int adis_write_reg_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct adis16480* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int adis16480_stop_device(struct iio_dev *indio_dev)
{
	struct adis16480 *st = iio_priv(indio_dev);
	int ret;

	ret = adis_write_reg_16(&st->adis, ADIS16480_REG_SLP_CNT, BIT(9));
	if (ret)
		dev_err(&indio_dev->dev,
			"Could not power down device: %d\n", ret);

	return ret;
}