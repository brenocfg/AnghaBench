#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ib_sa_device {int start_port; int end_port; TYPE_2__* port; int /*<<< orphan*/  event_handler; } ;
struct ib_device {int dummy; } ;
struct TYPE_3__ {int valid; } ;
struct TYPE_4__ {int port_num; int /*<<< orphan*/  agent; int /*<<< orphan*/  update_task; int /*<<< orphan*/  ib_cpi_work; TYPE_1__ classport_info; int /*<<< orphan*/  classport_lock; int /*<<< orphan*/ * sm_ah; int /*<<< orphan*/  ah_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_QPT_GSI ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_IB_EVENT_HANDLER (int /*<<< orphan*/ *,struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *)) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_register_event_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_register_mad_agent (struct ib_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ib_sa_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_sa_event ; 
 int /*<<< orphan*/  ib_set_client_data (struct ib_device*,int /*<<< orphan*/ *,struct ib_sa_device*) ; 
 int /*<<< orphan*/  ib_unregister_mad_agent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ib_sa_device*) ; 
 struct ib_sa_device* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port ; 
 scalar_t__ rdma_cap_ib_sa (struct ib_device*,int) ; 
 int rdma_end_port (struct ib_device*) ; 
 int rdma_start_port (struct ib_device*) ; 
 int /*<<< orphan*/  recv_handler ; 
 int /*<<< orphan*/  sa_client ; 
 int /*<<< orphan*/  send_handler ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  struct_size (struct ib_sa_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  update_ib_cpi ; 
 int /*<<< orphan*/  update_sm_ah (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ib_sa_add_one(struct ib_device *device)
{
	struct ib_sa_device *sa_dev;
	int s, e, i;
	int count = 0;

	s = rdma_start_port(device);
	e = rdma_end_port(device);

	sa_dev = kzalloc(struct_size(sa_dev, port, e - s + 1), GFP_KERNEL);
	if (!sa_dev)
		return;

	sa_dev->start_port = s;
	sa_dev->end_port   = e;

	for (i = 0; i <= e - s; ++i) {
		spin_lock_init(&sa_dev->port[i].ah_lock);
		if (!rdma_cap_ib_sa(device, i + 1))
			continue;

		sa_dev->port[i].sm_ah    = NULL;
		sa_dev->port[i].port_num = i + s;

		spin_lock_init(&sa_dev->port[i].classport_lock);
		sa_dev->port[i].classport_info.valid = false;

		sa_dev->port[i].agent =
			ib_register_mad_agent(device, i + s, IB_QPT_GSI,
					      NULL, 0, send_handler,
					      recv_handler, sa_dev, 0);
		if (IS_ERR(sa_dev->port[i].agent))
			goto err;

		INIT_WORK(&sa_dev->port[i].update_task, update_sm_ah);
		INIT_DELAYED_WORK(&sa_dev->port[i].ib_cpi_work,
				  update_ib_cpi);

		count++;
	}

	if (!count)
		goto free;

	ib_set_client_data(device, &sa_client, sa_dev);

	/*
	 * We register our event handler after everything is set up,
	 * and then update our cached info after the event handler is
	 * registered to avoid any problems if a port changes state
	 * during our initialization.
	 */

	INIT_IB_EVENT_HANDLER(&sa_dev->event_handler, device, ib_sa_event);
	ib_register_event_handler(&sa_dev->event_handler);

	for (i = 0; i <= e - s; ++i) {
		if (rdma_cap_ib_sa(device, i + 1))
			update_sm_ah(&sa_dev->port[i].update_task);
	}

	return;

err:
	while (--i >= 0) {
		if (rdma_cap_ib_sa(device, i + 1))
			ib_unregister_mad_agent(sa_dev->port[i].agent);
	}
free:
	kfree(sa_dev);
	return;
}