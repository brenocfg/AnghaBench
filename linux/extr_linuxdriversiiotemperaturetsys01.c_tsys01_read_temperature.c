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
typedef  int u32 ;
struct tsys01_dev {int (* convert_and_read ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ;scalar_t__* prom; int /*<<< orphan*/  lock; int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;
typedef  int s64 ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  TSYS01_ADC_READ ; 
 int /*<<< orphan*/  TSYS01_CONVERSION_START ; 
 int* coeff_mul ; 
 int div64_s64 (int,int) ; 
 struct tsys01_dev* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int tsys01_read_temperature(struct iio_dev *indio_dev,
				   s32 *temperature)
{
	int ret, i;
	u32 adc;
	s64 temp = 0;
	struct tsys01_dev *dev_data = iio_priv(indio_dev);

	mutex_lock(&dev_data->lock);
	ret = dev_data->convert_and_read(dev_data->client,
					 TSYS01_CONVERSION_START,
					 TSYS01_ADC_READ, 9000, &adc);
	mutex_unlock(&dev_data->lock);
	if (ret)
		return ret;

	adc >>= 8;

	/* Temperature algorithm */
	for (i = 4; i > 0; i--) {
		temp += coeff_mul[i] *
			(s64)dev_data->prom[5 - i];
		temp *= (s64)adc;
		temp = div64_s64(temp, 100000);
	}
	temp *= 10;
	temp += coeff_mul[0] * (s64)dev_data->prom[5];
	temp = div64_s64(temp, 100000);

	*temperature = temp;

	return 0;
}