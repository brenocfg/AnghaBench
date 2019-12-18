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
struct rm3100_data {int /*<<< orphan*/  conversion_time; int /*<<< orphan*/  measuring_done; scalar_t__ use_interrupt; struct regmap* regmap; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  RM3100_REG_STATUS ; 
 unsigned int RM3100_STATUS_DRDY ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rm3100_wait_measurement(struct rm3100_data *data)
{
	struct regmap *regmap = data->regmap;
	unsigned int val;
	int tries = 20;
	int ret;

	/*
	 * A read cycle of 400kbits i2c bus is about 20us, plus the time
	 * used for scheduling, a read cycle of fast mode of this device
	 * can reach 1.7ms, it may be possible for data to arrive just
	 * after we check the RM3100_REG_STATUS. In this case, irq_handler is
	 * called before measuring_done is reinitialized, it will wait
	 * forever for data that has already been ready.
	 * Reinitialize measuring_done before looking up makes sure we
	 * will always capture interrupt no matter when it happens.
	 */
	if (data->use_interrupt)
		reinit_completion(&data->measuring_done);

	ret = regmap_read(regmap, RM3100_REG_STATUS, &val);
	if (ret < 0)
		return ret;

	if ((val & RM3100_STATUS_DRDY) != RM3100_STATUS_DRDY) {
		if (data->use_interrupt) {
			ret = wait_for_completion_timeout(&data->measuring_done,
				msecs_to_jiffies(data->conversion_time));
			if (!ret)
				return -ETIMEDOUT;
		} else {
			do {
				usleep_range(1000, 5000);

				ret = regmap_read(regmap, RM3100_REG_STATUS,
						  &val);
				if (ret < 0)
					return ret;

				if (val & RM3100_STATUS_DRDY)
					break;
			} while (--tries);
			if (!tries)
				return -ETIMEDOUT;
		}
	}
	return 0;
}