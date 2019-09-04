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
struct tmp006_data {int config; int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int**) ; 
 int EINVAL ; 
 long IIO_CHAN_INFO_SAMP_FREQ ; 
 int /*<<< orphan*/  TMP006_CONFIG ; 
 int TMP006_CONFIG_CR_MASK ; 
 int TMP006_CONFIG_CR_SHIFT ; 
 int i2c_smbus_write_word_swapped (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct tmp006_data* iio_priv (struct iio_dev*) ; 
 int** tmp006_freqs ; 

__attribute__((used)) static int tmp006_write_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int val,
			    int val2,
			    long mask)
{
	struct tmp006_data *data = iio_priv(indio_dev);
	int i;

	if (mask != IIO_CHAN_INFO_SAMP_FREQ)
		return -EINVAL;

	for (i = 0; i < ARRAY_SIZE(tmp006_freqs); i++)
		if ((val == tmp006_freqs[i][0]) &&
		    (val2 == tmp006_freqs[i][1])) {
			data->config &= ~TMP006_CONFIG_CR_MASK;
			data->config |= i << TMP006_CONFIG_CR_SHIFT;

			return i2c_smbus_write_word_swapped(data->client,
							    TMP006_CONFIG,
							    data->config);

		}
	return -EINVAL;
}