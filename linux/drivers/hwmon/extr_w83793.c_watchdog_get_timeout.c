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
struct w83793_data {int watchdog_timeout; int /*<<< orphan*/  watchdog_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int watchdog_get_timeout(struct w83793_data *data)
{
	int timeout;

	mutex_lock(&data->watchdog_lock);
	timeout = data->watchdog_timeout * 60;
	mutex_unlock(&data->watchdog_lock);

	return timeout;
}