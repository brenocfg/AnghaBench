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
typedef  int /*<<< orphan*/  u16 ;
struct mma9553_data {int /*<<< orphan*/  mutex; TYPE_1__* client; scalar_t__ stepcnt_enabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MMA9551_APPID_PEDOMETER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int mma9551_read_status_word (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mma9553_is_any_event_enabled (struct mma9553_data*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mma9553_read_status_word(struct mma9553_data *data, u16 reg,
				    u16 *tmp)
{
	bool powered_on;
	int ret;

	/*
	 * The HW only counts steps and other dependent
	 * parameters (speed, distance, calories, activity)
	 * if power is on (from enabling an event or the
	 * step counter).
	 */
	powered_on = mma9553_is_any_event_enabled(data, false, 0) ||
		     data->stepcnt_enabled;
	if (!powered_on) {
		dev_err(&data->client->dev, "No channels enabled\n");
		return -EINVAL;
	}

	mutex_lock(&data->mutex);
	ret = mma9551_read_status_word(data->client, MMA9551_APPID_PEDOMETER,
				       reg, tmp);
	mutex_unlock(&data->mutex);
	return ret;
}