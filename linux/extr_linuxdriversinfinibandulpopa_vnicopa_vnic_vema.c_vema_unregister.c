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
struct opa_vnic_vema_port {int /*<<< orphan*/  event_handler; int /*<<< orphan*/  vport_idr; int /*<<< orphan*/  lock; int /*<<< orphan*/ * mad_agent; } ;
struct opa_vnic_ctrl_port {int num_ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_unregister_event_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_unregister_mad_agent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_for_each (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct opa_vnic_vema_port* vema_get_port (struct opa_vnic_ctrl_port*,int) ; 
 int /*<<< orphan*/  vema_rem_vport ; 

__attribute__((used)) static void vema_unregister(struct opa_vnic_ctrl_port *cport)
{
	int i;

	for (i = 1; i <= cport->num_ports; i++) {
		struct opa_vnic_vema_port *port = vema_get_port(cport, i);

		if (!port->mad_agent)
			continue;

		/* Lock ensures no MAD is being processed */
		mutex_lock(&port->lock);
		idr_for_each(&port->vport_idr, vema_rem_vport, NULL);
		mutex_unlock(&port->lock);

		ib_unregister_mad_agent(port->mad_agent);
		port->mad_agent = NULL;
		mutex_destroy(&port->lock);
		idr_destroy(&port->vport_idr);
		ib_unregister_event_handler(&port->event_handler);
	}
}