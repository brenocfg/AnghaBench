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
struct adis16136 {int /*<<< orphan*/  adis; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADIS16136_REG_SLP_CTRL ; 
 int adis_write_reg_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct adis16136* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int adis16136_stop_device(struct iio_dev *indio_dev)
{
	struct adis16136 *adis16136 = iio_priv(indio_dev);
	int ret;

	ret = adis_write_reg_16(&adis16136->adis, ADIS16136_REG_SLP_CTRL, 0xff);
	if (ret)
		dev_err(&indio_dev->dev,
			"Could not power down device: %d\n", ret);

	return ret;
}