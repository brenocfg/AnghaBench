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
typedef  int u16 ;
struct tmp007_data {int config; int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int**) ; 
 int EINVAL ; 
 long IIO_CHAN_INFO_SAMP_FREQ ; 
 int /*<<< orphan*/  TMP007_CONFIG ; 
 int TMP007_CONFIG_CR_MASK ; 
 int TMP007_CONFIG_CR_SHIFT ; 
 int i2c_smbus_write_word_swapped (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct tmp007_data* iio_priv (struct iio_dev*) ; 
 int** tmp007_avgs ; 

__attribute__((used)) static int tmp007_write_raw(struct iio_dev *indio_dev,
		struct iio_chan_spec const *channel, int val,
		int val2, long mask)
{
	struct tmp007_data *data = iio_priv(indio_dev);
	int i;
	u16 tmp;

	if (mask == IIO_CHAN_INFO_SAMP_FREQ) {
		for (i = 0; i < ARRAY_SIZE(tmp007_avgs); i++) {
			if ((val == tmp007_avgs[i][0]) &&
			(val2 == tmp007_avgs[i][1])) {
				tmp = data->config & ~TMP007_CONFIG_CR_MASK;
				tmp |= (i << TMP007_CONFIG_CR_SHIFT);

				return i2c_smbus_write_word_swapped(data->client,
								TMP007_CONFIG,
								data->config = tmp);
			}
		}
	}

	return -EINVAL;
}