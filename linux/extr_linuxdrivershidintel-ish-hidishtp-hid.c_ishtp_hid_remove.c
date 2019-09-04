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
struct ishtp_cl_data {int num_hid_devices; TYPE_1__** hid_sensor_hubs; } ;
struct TYPE_2__ {int /*<<< orphan*/  driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  hid_destroy_device (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void ishtp_hid_remove(struct ishtp_cl_data *client_data)
{
	int i;

	for (i = 0; i < client_data->num_hid_devices; ++i) {
		if (client_data->hid_sensor_hubs[i]) {
			kfree(client_data->hid_sensor_hubs[i]->driver_data);
			hid_destroy_device(client_data->hid_sensor_hubs[i]);
			client_data->hid_sensor_hubs[i] = NULL;
		}
	}
}