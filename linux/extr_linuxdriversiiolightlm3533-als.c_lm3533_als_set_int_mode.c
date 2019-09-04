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
struct lm3533_als {int /*<<< orphan*/  lm3533; } ;
struct iio_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ LM3533_ALS_INT_ENABLE_MASK ; 
 int /*<<< orphan*/  LM3533_REG_ALS_ZONE_INFO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct lm3533_als* iio_priv (struct iio_dev*) ; 
 int lm3533_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int lm3533_als_set_int_mode(struct iio_dev *indio_dev, int enable)
{
	struct lm3533_als *als = iio_priv(indio_dev);
	u8 mask = LM3533_ALS_INT_ENABLE_MASK;
	u8 val;
	int ret;

	if (enable)
		val = mask;
	else
		val = 0;

	ret = lm3533_update(als->lm3533, LM3533_REG_ALS_ZONE_INFO, val, mask);
	if (ret) {
		dev_err(&indio_dev->dev, "failed to set int mode %d\n",
								enable);
		return ret;
	}

	return 0;
}