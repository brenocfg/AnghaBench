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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
struct bma220_data {int* tx_buf; int /*<<< orphan*/  lock; TYPE_1__* spi_device; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int**) ; 
 int BMA220_REG_RANGE ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_SCALE 128 
 int** bma220_scale_table ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct bma220_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int spi_write (TYPE_1__*,int*,int) ; 

__attribute__((used)) static int bma220_write_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int val, int val2, long mask)
{
	int i;
	int ret;
	int index = -1;
	struct bma220_data *data = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_SCALE:
		for (i = 0; i < ARRAY_SIZE(bma220_scale_table); i++)
			if (val == bma220_scale_table[i][0] &&
			    val2 == bma220_scale_table[i][1]) {
				index = i;
				break;
			}
		if (index < 0)
			return -EINVAL;

		mutex_lock(&data->lock);
		data->tx_buf[0] = BMA220_REG_RANGE;
		data->tx_buf[1] = index;
		ret = spi_write(data->spi_device, data->tx_buf,
				sizeof(data->tx_buf));
		if (ret < 0)
			dev_err(&data->spi_device->dev,
				"failed to set measurement range\n");
		mutex_unlock(&data->lock);

		return 0;
	}

	return -EINVAL;
}