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
struct adis16480 {int /*<<< orphan*/  adis; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADIS16480_REG_DEC_RATE ; 
 int EINVAL ; 
 int adis_write_reg_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 struct adis16480* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int adis16480_set_freq(struct iio_dev *indio_dev, int val, int val2)
{
	struct adis16480 *st = iio_priv(indio_dev);
	unsigned int t;

	t =  val * 1000 + val2 / 1000;
	if (t <= 0)
		return -EINVAL;

	t = 2460000 / t;
	if (t > 2048)
		t = 2048;

	if (t != 0)
		t--;

	return adis_write_reg_16(&st->adis, ADIS16480_REG_DEC_RATE, t);
}