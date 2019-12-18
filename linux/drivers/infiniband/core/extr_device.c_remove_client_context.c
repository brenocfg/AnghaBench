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
struct ib_device {int /*<<< orphan*/  client_data; int /*<<< orphan*/  client_data_rwsem; } ;
struct ib_client {int /*<<< orphan*/  (* remove ) (struct ib_device*,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_DATA_REGISTERED ; 
 int /*<<< orphan*/  clients ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_client_put (struct ib_client*) ; 
 int /*<<< orphan*/  ib_device_put (struct ib_device*) ; 
 int /*<<< orphan*/  stub1 (struct ib_device*,void*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_clear_mark (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_erase (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  xa_get_mark (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 void* xa_load (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void remove_client_context(struct ib_device *device,
				  unsigned int client_id)
{
	struct ib_client *client;
	void *client_data;

	down_write(&device->client_data_rwsem);
	if (!xa_get_mark(&device->client_data, client_id,
			 CLIENT_DATA_REGISTERED)) {
		up_write(&device->client_data_rwsem);
		return;
	}
	client_data = xa_load(&device->client_data, client_id);
	xa_clear_mark(&device->client_data, client_id, CLIENT_DATA_REGISTERED);
	client = xa_load(&clients, client_id);
	up_write(&device->client_data_rwsem);

	/*
	 * Notice we cannot be holding any exclusive locks when calling the
	 * remove callback as the remove callback can recurse back into any
	 * public functions in this module and thus try for any locks those
	 * functions take.
	 *
	 * For this reason clients and drivers should not call the
	 * unregistration functions will holdling any locks.
	 */
	if (client->remove)
		client->remove(device, client_data);

	xa_erase(&device->client_data, client_id);
	ib_device_put(device);
	ib_client_put(client);
}