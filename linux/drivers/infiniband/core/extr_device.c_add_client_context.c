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
struct ib_device {int /*<<< orphan*/  client_data_rwsem; int /*<<< orphan*/  client_data; int /*<<< orphan*/  refcount; int /*<<< orphan*/  kverbs_provider; } ;
struct ib_client {int /*<<< orphan*/  client_id; int /*<<< orphan*/  (* add ) (struct ib_device*) ;int /*<<< orphan*/  uses; int /*<<< orphan*/  no_kverbs_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_DATA_REGISTERED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  downgrade_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_client_put (struct ib_client*) ; 
 int /*<<< orphan*/  ib_device_put (struct ib_device*) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ib_device*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int xa_err (int /*<<< orphan*/ ) ; 
 scalar_t__ xa_get_mark (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_set_mark (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_client_context(struct ib_device *device,
			      struct ib_client *client)
{
	int ret = 0;

	if (!device->kverbs_provider && !client->no_kverbs_req)
		return 0;

	down_write(&device->client_data_rwsem);
	/*
	 * So long as the client is registered hold both the client and device
	 * unregistration locks.
	 */
	if (!refcount_inc_not_zero(&client->uses))
		goto out_unlock;
	refcount_inc(&device->refcount);

	/*
	 * Another caller to add_client_context got here first and has already
	 * completely initialized context.
	 */
	if (xa_get_mark(&device->client_data, client->client_id,
		    CLIENT_DATA_REGISTERED))
		goto out;

	ret = xa_err(xa_store(&device->client_data, client->client_id, NULL,
			      GFP_KERNEL));
	if (ret)
		goto out;
	downgrade_write(&device->client_data_rwsem);
	if (client->add)
		client->add(device);

	/* Readers shall not see a client until add has been completed */
	xa_set_mark(&device->client_data, client->client_id,
		    CLIENT_DATA_REGISTERED);
	up_read(&device->client_data_rwsem);
	return 0;

out:
	ib_device_put(device);
	ib_client_put(client);
out_unlock:
	up_write(&device->client_data_rwsem);
	return ret;
}