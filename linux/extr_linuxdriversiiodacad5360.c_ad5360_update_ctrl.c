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
struct ad5360_state {unsigned int ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD5360_CMD_SPECIAL_FUNCTION ; 
 int /*<<< orphan*/  AD5360_REG_SF_CTRL ; 
 unsigned int ad5360_write_unlocked (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 struct ad5360_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad5360_update_ctrl(struct iio_dev *indio_dev, unsigned int set,
	unsigned int clr)
{
	struct ad5360_state *st = iio_priv(indio_dev);
	unsigned int ret;

	mutex_lock(&indio_dev->mlock);

	st->ctrl |= set;
	st->ctrl &= ~clr;

	ret = ad5360_write_unlocked(indio_dev, AD5360_CMD_SPECIAL_FUNCTION,
			AD5360_REG_SF_CTRL, st->ctrl, 0);

	mutex_unlock(&indio_dev->mlock);

	return ret;
}