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
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct ad5421_state {unsigned int ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD5421_REG_CTRL ; 
 unsigned int ad5421_write_unlocked (struct iio_dev*,int /*<<< orphan*/ ,unsigned int) ; 
 struct ad5421_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad5421_update_ctrl(struct iio_dev *indio_dev, unsigned int set,
	unsigned int clr)
{
	struct ad5421_state *st = iio_priv(indio_dev);
	unsigned int ret;

	mutex_lock(&indio_dev->mlock);

	st->ctrl &= ~clr;
	st->ctrl |= set;

	ret = ad5421_write_unlocked(indio_dev, AD5421_REG_CTRL, st->ctrl);

	mutex_unlock(&indio_dev->mlock);

	return ret;
}