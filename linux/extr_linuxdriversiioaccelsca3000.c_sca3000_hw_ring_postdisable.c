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
struct sca3000_state {int* rx; int /*<<< orphan*/  lock; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCA3000_REG_INT_MASK_ADDR ; 
 int SCA3000_REG_INT_MASK_RING_HALF ; 
 int __sca3000_hw_ring_state_set (struct iio_dev*,int /*<<< orphan*/ ) ; 
 struct sca3000_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sca3000_read_data_short (struct sca3000_state*,int /*<<< orphan*/ ,int) ; 
 int sca3000_write_reg (struct sca3000_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sca3000_hw_ring_postdisable(struct iio_dev *indio_dev)
{
	int ret;
	struct sca3000_state *st = iio_priv(indio_dev);

	ret = __sca3000_hw_ring_state_set(indio_dev, 0);
	if (ret)
		return ret;

	/* Disable the 50% full interrupt */
	mutex_lock(&st->lock);

	ret = sca3000_read_data_short(st, SCA3000_REG_INT_MASK_ADDR, 1);
	if (ret)
		goto unlock;
	ret = sca3000_write_reg(st,
				SCA3000_REG_INT_MASK_ADDR,
				st->rx[0] & ~SCA3000_REG_INT_MASK_RING_HALF);
unlock:
	mutex_unlock(&st->lock);
	return ret;
}