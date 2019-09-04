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
struct tcs3414_data {int /*<<< orphan*/  control; int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCS3414_CONTROL ; 
 int /*<<< orphan*/  TCS3414_CONTROL_ADC_EN ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tcs3414_data* iio_priv (struct iio_dev*) ; 
 int iio_triggered_buffer_predisable (struct iio_dev*) ; 

__attribute__((used)) static int tcs3414_buffer_predisable(struct iio_dev *indio_dev)
{
	struct tcs3414_data *data = iio_priv(indio_dev);
	int ret;

	ret = iio_triggered_buffer_predisable(indio_dev);
	if (ret < 0)
		return ret;

	data->control &= ~TCS3414_CONTROL_ADC_EN;
	return i2c_smbus_write_byte_data(data->client, TCS3414_CONTROL,
		data->control);
}