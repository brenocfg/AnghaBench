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
struct ib_device {TYPE_1__* port_pkey_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  pkey_list; int /*<<< orphan*/  list_lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_1__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int rdma_end_port (struct ib_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int setup_port_pkey_list(struct ib_device *device)
{
	int i;

	/**
	 * device->port_pkey_list is indexed directly by the port number,
	 * Therefore it is declared as a 1 based array with potential empty
	 * slots at the beginning.
	 */
	device->port_pkey_list = kcalloc(rdma_end_port(device) + 1,
					 sizeof(*device->port_pkey_list),
					 GFP_KERNEL);

	if (!device->port_pkey_list)
		return -ENOMEM;

	for (i = 0; i < (rdma_end_port(device) + 1); i++) {
		spin_lock_init(&device->port_pkey_list[i].list_lock);
		INIT_LIST_HEAD(&device->port_pkey_list[i].pkey_list);
	}

	return 0;
}