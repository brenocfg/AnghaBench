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
struct mcast_port {int /*<<< orphan*/  comp; } ;
struct mcast_device {int end_port; int start_port; struct mcast_port* port; int /*<<< orphan*/  event_handler; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  deref_port (struct mcast_port*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_unregister_event_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mcast_device*) ; 
 int /*<<< orphan*/  mcast_wq ; 
 scalar_t__ rdma_cap_ib_mcast (struct ib_device*,int) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mcast_remove_one(struct ib_device *device, void *client_data)
{
	struct mcast_device *dev = client_data;
	struct mcast_port *port;
	int i;

	if (!dev)
		return;

	ib_unregister_event_handler(&dev->event_handler);
	flush_workqueue(mcast_wq);

	for (i = 0; i <= dev->end_port - dev->start_port; i++) {
		if (rdma_cap_ib_mcast(device, dev->start_port + i)) {
			port = &dev->port[i];
			deref_port(port);
			wait_for_completion(&port->comp);
		}
	}

	kfree(dev);
}