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
typedef  int uint16_t ;
typedef  scalar_t__ u8 ;
struct w1_slave {TYPE_1__* master; } ;
typedef  int int16_t ;
struct TYPE_2__ {int /*<<< orphan*/  bus_mutex; } ;

/* Variables and functions */
 unsigned int DS2438_MAX_CONVERSION_TIME ; 
 int /*<<< orphan*/  DS2438_PAGE_SIZE ; 
 size_t DS2438_TEMP_LSB ; 
 size_t DS2438_TEMP_MSB ; 
 int /*<<< orphan*/  W1_DS2438_CONVERT_TEMP ; 
 unsigned int W1_DS2438_RETRIES ; 
 unsigned long msleep_interruptible (unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ w1_ds2438_get_page (struct w1_slave*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ w1_reset_select_slave (struct w1_slave*) ; 
 int /*<<< orphan*/  w1_write_8 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int w1_ds2438_get_temperature(struct w1_slave *sl, int16_t *temperature)
{
	unsigned int retries = W1_DS2438_RETRIES;
	u8 w1_buf[DS2438_PAGE_SIZE + 1 /*for CRC*/];
	unsigned int tm = DS2438_MAX_CONVERSION_TIME;
	unsigned long sleep_rem;
	int ret;

	mutex_lock(&sl->master->bus_mutex);

	while (retries--) {
		if (w1_reset_select_slave(sl))
			continue;
		w1_write_8(sl->master, W1_DS2438_CONVERT_TEMP);

		mutex_unlock(&sl->master->bus_mutex);
		sleep_rem = msleep_interruptible(tm);
		if (sleep_rem != 0) {
			ret = -1;
			goto post_unlock;
		}

		if (mutex_lock_interruptible(&sl->master->bus_mutex) != 0) {
			ret = -1;
			goto post_unlock;
		}

		break;
	}

	if (w1_ds2438_get_page(sl, 0, w1_buf) == 0) {
		*temperature = (((int16_t) w1_buf[DS2438_TEMP_MSB]) << 8) | ((uint16_t) w1_buf[DS2438_TEMP_LSB]);
		ret = 0;
	} else
		ret = -1;

	mutex_unlock(&sl->master->bus_mutex);

post_unlock:
	return ret;
}