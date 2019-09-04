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
typedef  scalar_t__ u8 ;
struct lm3533_als {int /*<<< orphan*/  thresh_mutex; int /*<<< orphan*/  lm3533; } ;
struct iio_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int LM3533_ALS_THRESH_MAX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct lm3533_als* iio_priv (struct iio_dev*) ; 
 scalar_t__ lm3533_als_get_threshold_reg (unsigned int,int) ; 
 int lm3533_read (int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int lm3533_write (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lm3533_als_set_threshold(struct iio_dev *indio_dev, unsigned nr,
							bool raising, u8 val)
{
	struct lm3533_als *als = iio_priv(indio_dev);
	u8 val2;
	u8 reg, reg2;
	int ret;

	if (nr > LM3533_ALS_THRESH_MAX)
		return -EINVAL;

	reg = lm3533_als_get_threshold_reg(nr, raising);
	reg2 = lm3533_als_get_threshold_reg(nr, !raising);

	mutex_lock(&als->thresh_mutex);
	ret = lm3533_read(als->lm3533, reg2, &val2);
	if (ret) {
		dev_err(&indio_dev->dev, "failed to get threshold\n");
		goto out;
	}
	/*
	 * This device does not allow negative hysteresis (in fact, it uses
	 * whichever value is smaller as the lower bound) so we need to make
	 * sure that thresh_falling <= thresh_raising.
	 */
	if ((raising && (val < val2)) || (!raising && (val > val2))) {
		ret = -EINVAL;
		goto out;
	}

	ret = lm3533_write(als->lm3533, reg, val);
	if (ret) {
		dev_err(&indio_dev->dev, "failed to set threshold\n");
		goto out;
	}
out:
	mutex_unlock(&als->thresh_mutex);

	return ret;
}