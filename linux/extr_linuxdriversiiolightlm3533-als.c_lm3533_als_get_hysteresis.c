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
struct lm3533_als {int /*<<< orphan*/  thresh_mutex; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int LM3533_ALS_THRESH_MAX ; 
 struct lm3533_als* iio_priv (struct iio_dev*) ; 
 int lm3533_als_get_threshold (struct iio_dev*,unsigned int,int,scalar_t__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lm3533_als_get_hysteresis(struct iio_dev *indio_dev, unsigned nr,
								u8 *val)
{
	struct lm3533_als *als = iio_priv(indio_dev);
	u8 falling;
	u8 raising;
	int ret;

	if (nr > LM3533_ALS_THRESH_MAX)
		return -EINVAL;

	mutex_lock(&als->thresh_mutex);
	ret = lm3533_als_get_threshold(indio_dev, nr, false, &falling);
	if (ret)
		goto out;
	ret = lm3533_als_get_threshold(indio_dev, nr, true, &raising);
	if (ret)
		goto out;

	*val = raising - falling;
out:
	mutex_unlock(&als->thresh_mutex);

	return ret;
}