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
struct ad7768_state {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ad7768_spi_reg_read (struct ad7768_state*,unsigned int,int) ; 
 int ad7768_spi_reg_write (struct ad7768_state*,unsigned int,unsigned int) ; 
 struct ad7768_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad7768_reg_access(struct iio_dev *indio_dev,
			     unsigned int reg,
			     unsigned int writeval,
			     unsigned int *readval)
{
	struct ad7768_state *st = iio_priv(indio_dev);
	int ret;

	mutex_lock(&st->lock);
	if (readval) {
		ret = ad7768_spi_reg_read(st, reg, 1);
		if (ret < 0)
			goto err_unlock;
		*readval = ret;
		ret = 0;
	} else {
		ret = ad7768_spi_reg_write(st, reg, writeval);
	}
err_unlock:
	mutex_unlock(&st->lock);

	return ret;
}