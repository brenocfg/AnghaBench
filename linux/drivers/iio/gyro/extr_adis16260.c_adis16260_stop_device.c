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
typedef  int /*<<< orphan*/  u16 ;
struct iio_dev {int /*<<< orphan*/  dev; } ;
struct adis16260 {int /*<<< orphan*/  adis; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADIS16260_SLP_CNT ; 
 int /*<<< orphan*/  ADIS16260_SLP_CNT_POWER_OFF ; 
 int adis_write_reg_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct adis16260* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int adis16260_stop_device(struct iio_dev *indio_dev)
{
	struct adis16260 *adis16260 = iio_priv(indio_dev);
	int ret;
	u16 val = ADIS16260_SLP_CNT_POWER_OFF;

	ret = adis_write_reg_16(&adis16260->adis, ADIS16260_SLP_CNT, val);
	if (ret)
		dev_err(&indio_dev->dev, "problem with turning device off: SLP_CNT");

	return ret;
}