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
struct w83793_data {int /*<<< orphan*/  watchdog_lock; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  W83793_REG_WDT_LOCK ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  w83793_write_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int watchdog_disable(struct w83793_data *data)
{
	int ret = 0;

	mutex_lock(&data->watchdog_lock);
	if (!data->client) {
		ret = -ENODEV;
		goto leave;
	}

	/* Disable Soft Watchdog */
	w83793_write_value(data->client, W83793_REG_WDT_LOCK, 0xAA);

leave:
	mutex_unlock(&data->watchdog_lock);
	return ret;
}