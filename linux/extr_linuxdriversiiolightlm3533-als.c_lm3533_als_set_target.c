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
typedef  int /*<<< orphan*/  u8 ;
struct lm3533_als {int /*<<< orphan*/  lm3533; } ;
struct iio_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int LM3533_ALS_CHANNEL_CURRENT_MAX ; 
 unsigned int LM3533_ALS_ZONE_MAX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct lm3533_als* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  lm3533_als_get_target_reg (unsigned int,unsigned int) ; 
 int lm3533_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm3533_als_set_target(struct iio_dev *indio_dev, unsigned channel,
							unsigned zone, u8 val)
{
	struct lm3533_als *als = iio_priv(indio_dev);
	u8 reg;
	int ret;

	if (channel > LM3533_ALS_CHANNEL_CURRENT_MAX)
		return -EINVAL;

	if (zone > LM3533_ALS_ZONE_MAX)
		return -EINVAL;

	reg = lm3533_als_get_target_reg(channel, zone);
	ret = lm3533_write(als->lm3533, reg, val);
	if (ret)
		dev_err(&indio_dev->dev, "failed to set target current\n");

	return ret;
}