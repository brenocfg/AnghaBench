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
struct ad9523_state {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned int AD9523_R1B ; 
 int /*<<< orphan*/  ad9523_io_update (struct iio_dev*) ; 
 int ad9523_read (struct iio_dev*,unsigned int) ; 
 int ad9523_write (struct iio_dev*,unsigned int,unsigned int) ; 
 struct ad9523_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad9523_reg_access(struct iio_dev *indio_dev,
			      unsigned int reg, unsigned int writeval,
			      unsigned int *readval)
{
	struct ad9523_state *st = iio_priv(indio_dev);
	int ret;

	mutex_lock(&st->lock);
	if (readval == NULL) {
		ret = ad9523_write(indio_dev, reg | AD9523_R1B, writeval);
		ad9523_io_update(indio_dev);
	} else {
		ret = ad9523_read(indio_dev, reg | AD9523_R1B);
		if (ret < 0)
			goto out_unlock;
		*readval = ret;
		ret = 0;
	}

out_unlock:
	mutex_unlock(&st->lock);

	return ret;
}