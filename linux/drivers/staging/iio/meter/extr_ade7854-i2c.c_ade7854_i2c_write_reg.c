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
typedef  int u16 ;
struct iio_dev {int dummy; } ;
struct device {int dummy; } ;
struct ade7854_state {int* tx; int /*<<< orphan*/  buf_lock; int /*<<< orphan*/  i2c; } ;

/* Variables and functions */
 int EINVAL ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 int i2c_master_send (int /*<<< orphan*/ ,int*,int) ; 
 struct ade7854_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ade7854_i2c_write_reg(struct device *dev,
				 u16 reg_address,
				 u32 val,
				 int bits)
{
	int ret;
	int count;
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ade7854_state *st = iio_priv(indio_dev);

	mutex_lock(&st->buf_lock);
	st->tx[0] = (reg_address >> 8) & 0xFF;
	st->tx[1] = reg_address & 0xFF;

	switch (bits) {
	case 8:
		st->tx[2] = val & 0xFF;
		count = 3;
		break;
	case 16:
		st->tx[2] = (val >> 8) & 0xFF;
		st->tx[3] = val & 0xFF;
		count = 4;
		break;
	case 24:
		st->tx[2] = (val >> 16) & 0xFF;
		st->tx[3] = (val >> 8) & 0xFF;
		st->tx[4] = val & 0xFF;
		count = 5;
		break;
	case 32:
		st->tx[2] = (val >> 24) & 0xFF;
		st->tx[3] = (val >> 16) & 0xFF;
		st->tx[4] = (val >> 8) & 0xFF;
		st->tx[5] = val & 0xFF;
		count = 6;
		break;
	default:
		ret = -EINVAL;
		goto unlock;
	}

	ret = i2c_master_send(st->i2c, st->tx, count);

unlock:
	mutex_unlock(&st->buf_lock);

	return ret < 0 ? ret : 0;
}