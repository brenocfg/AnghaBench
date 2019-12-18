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
struct ibmpex_bmc_data {int valid; int num_sensors; int /*<<< orphan*/  lock; scalar_t__ last_updated; int /*<<< orphan*/  rx_msg_data; TYPE_1__* sensors; } ;
struct TYPE_2__ {void** values; int /*<<< orphan*/  in_use; } ;

/* Variables and functions */
 scalar_t__ REFRESH_INTERVAL ; 
 void* extract_value (int /*<<< orphan*/ ,int) ; 
 int ibmpex_query_sensor_data (struct ibmpex_bmc_data*,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void ibmpex_update_device(struct ibmpex_bmc_data *data)
{
	int i, err;

	mutex_lock(&data->lock);
	if (time_before(jiffies, data->last_updated + REFRESH_INTERVAL) &&
	    data->valid)
		goto out;

	for (i = 0; i < data->num_sensors; i++) {
		if (!data->sensors[i].in_use)
			continue;
		err = ibmpex_query_sensor_data(data, i);
		if (err)
			continue;
		data->sensors[i].values[0] =
			extract_value(data->rx_msg_data, 16);
		data->sensors[i].values[1] =
			extract_value(data->rx_msg_data, 18);
		data->sensors[i].values[2] =
			extract_value(data->rx_msg_data, 20);
	}

	data->last_updated = jiffies;
	data->valid = 1;

out:
	mutex_unlock(&data->lock);
}