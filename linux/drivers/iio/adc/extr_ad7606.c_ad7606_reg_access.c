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
struct ad7606_state {int /*<<< orphan*/  lock; TYPE_1__* bops; } ;
struct TYPE_2__ {int (* reg_read ) (struct ad7606_state*,unsigned int) ;int (* reg_write ) (struct ad7606_state*,unsigned int,unsigned int) ;} ;

/* Variables and functions */
 struct ad7606_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct ad7606_state*,unsigned int) ; 
 int stub2 (struct ad7606_state*,unsigned int,unsigned int) ; 

__attribute__((used)) static int ad7606_reg_access(struct iio_dev *indio_dev,
			     unsigned int reg,
			     unsigned int writeval,
			     unsigned int *readval)
{
	struct ad7606_state *st = iio_priv(indio_dev);
	int ret;

	mutex_lock(&st->lock);
	if (readval) {
		ret = st->bops->reg_read(st, reg);
		if (ret < 0)
			goto err_unlock;
		*readval = ret;
		ret = 0;
	} else {
		ret = st->bops->reg_write(st, reg, writeval);
	}
err_unlock:
	mutex_unlock(&st->lock);
	return ret;
}