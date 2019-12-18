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
struct w1_slave {scalar_t__* family_data; struct w1_master* master; } ;
struct w1_master {int /*<<< orphan*/  bus_mutex; } ;
struct therm_info {scalar_t__* rom; int verdict; scalar_t__ crc; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINTR ; 
 int ENODEV ; 
 int /*<<< orphan*/  THERM_REFCNT (scalar_t__*) ; 
 int /*<<< orphan*/  W1_CONVERT_TEMP ; 
 int /*<<< orphan*/  W1_READ_PSUPPLY ; 
 int /*<<< orphan*/  W1_READ_SCRATCHPAD ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 unsigned long msleep_interruptible (unsigned int) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ w1_calc_crc8 (scalar_t__*,int) ; 
 int /*<<< orphan*/  w1_next_pullup (struct w1_master*,unsigned int) ; 
 scalar_t__ w1_read_8 (struct w1_master*) ; 
 int w1_read_block (struct w1_master*,scalar_t__*,int) ; 
 scalar_t__ w1_reset_select_slave (struct w1_slave*) ; 
 int w1_strong_pullup ; 
 int /*<<< orphan*/  w1_write_8 (struct w1_master*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t read_therm(struct device *device,
			  struct w1_slave *sl, struct therm_info *info)
{
	struct w1_master *dev = sl->master;
	u8 external_power;
	int ret, max_trying = 10;
	u8 *family_data = sl->family_data;

	if (!family_data) {
		ret = -ENODEV;
		goto error;
	}

	/* prevent the slave from going away in sleep */
	atomic_inc(THERM_REFCNT(family_data));

	ret = mutex_lock_interruptible(&dev->bus_mutex);
	if (ret != 0)
		goto dec_refcnt;

	memset(info->rom, 0, sizeof(info->rom));

	while (max_trying--) {

		info->verdict = 0;
		info->crc = 0;

		if (!w1_reset_select_slave(sl)) {
			int count = 0;
			unsigned int tm = 750;
			unsigned long sleep_rem;

			w1_write_8(dev, W1_READ_PSUPPLY);
			external_power = w1_read_8(dev);

			if (w1_reset_select_slave(sl))
				continue;

			/* 750ms strong pullup (or delay) after the convert */
			if (w1_strong_pullup == 2 ||
					(!external_power && w1_strong_pullup))
				w1_next_pullup(dev, tm);

			w1_write_8(dev, W1_CONVERT_TEMP);

			if (external_power) {
				mutex_unlock(&dev->bus_mutex);

				sleep_rem = msleep_interruptible(tm);
				if (sleep_rem != 0) {
					ret = -EINTR;
					goto dec_refcnt;
				}

				ret = mutex_lock_interruptible(&dev->bus_mutex);
				if (ret != 0)
					goto dec_refcnt;
			} else if (!w1_strong_pullup) {
				sleep_rem = msleep_interruptible(tm);
				if (sleep_rem != 0) {
					ret = -EINTR;
					goto mt_unlock;
				}
			}

			if (!w1_reset_select_slave(sl)) {

				w1_write_8(dev, W1_READ_SCRATCHPAD);
				count = w1_read_block(dev, info->rom, 9);
				if (count != 9) {
					dev_warn(device, "w1_read_block() "
						"returned %u instead of 9.\n",
						count);
				}

				info->crc = w1_calc_crc8(info->rom, 8);

				if (info->rom[8] == info->crc)
					info->verdict = 1;
			}
		}

		if (info->verdict)
			break;
	}

mt_unlock:
	mutex_unlock(&dev->bus_mutex);
dec_refcnt:
	atomic_dec(THERM_REFCNT(family_data));
error:
	return ret;
}