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
typedef  int u8 ;
struct sca3000_state {int* rx; int /*<<< orphan*/  lock; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCA3000_REG_BUF_COUNT_ADDR ; 
 int SCA3000_REG_INT_STATUS_HALF ; 
 int /*<<< orphan*/  SCA3000_REG_RING_OUT_ADDR ; 
 struct sca3000_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers (struct iio_dev*,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sca3000_read_data (struct sca3000_state*,int /*<<< orphan*/ ,int*,int) ; 
 int sca3000_read_data_short (struct sca3000_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sca3000_ring_int_process(u8 val, struct iio_dev *indio_dev)
{
	struct sca3000_state *st = iio_priv(indio_dev);
	int ret, i, num_available;

	mutex_lock(&st->lock);

	if (val & SCA3000_REG_INT_STATUS_HALF) {
		ret = sca3000_read_data_short(st, SCA3000_REG_BUF_COUNT_ADDR,
					      1);
		if (ret)
			goto error_ret;
		num_available = st->rx[0];
		/*
		 * num_available is the total number of samples available
		 * i.e. number of time points * number of channels.
		 */
		ret = sca3000_read_data(st, SCA3000_REG_RING_OUT_ADDR, st->rx,
					num_available * 2);
		if (ret)
			goto error_ret;
		for (i = 0; i < num_available / 3; i++) {
			/*
			 * Dirty hack to cover for 11 bit in fifo, 13 bit
			 * direct reading.
			 *
			 * In theory the bottom two bits are undefined.
			 * In reality they appear to always be 0.
			 */
			iio_push_to_buffers(indio_dev, st->rx + i * 3 * 2);
		}
	}
error_ret:
	mutex_unlock(&st->lock);
}