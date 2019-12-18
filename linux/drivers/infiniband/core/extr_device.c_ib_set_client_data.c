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
struct ib_device {int /*<<< orphan*/  client_data; } ;
struct ib_client {int /*<<< orphan*/  client_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (void*) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_is_err (void*) ; 
 void* xa_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

void ib_set_client_data(struct ib_device *device, struct ib_client *client,
			void *data)
{
	void *rc;

	if (WARN_ON(IS_ERR(data)))
		data = NULL;

	rc = xa_store(&device->client_data, client->client_id, data,
		      GFP_KERNEL);
	WARN_ON(xa_is_err(rc));
}