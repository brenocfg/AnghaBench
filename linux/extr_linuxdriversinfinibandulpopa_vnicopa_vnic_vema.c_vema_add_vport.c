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
typedef  scalar_t__ u8 ;
struct opa_vnic_vema_port {int /*<<< orphan*/  vport_idr; int /*<<< orphan*/  port_num; struct opa_vnic_ctrl_port* cport; } ;
struct opa_vnic_ctrl_port {int /*<<< orphan*/  ibdev; } ;
struct opa_vnic_adapter {struct opa_vnic_ctrl_port* cport; } ;

/* Variables and functions */
 struct opa_vnic_adapter* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  IS_ERR (struct opa_vnic_adapter*) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct opa_vnic_adapter*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 struct opa_vnic_adapter* opa_vnic_add_netdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  opa_vnic_rem_netdev (struct opa_vnic_adapter*) ; 

__attribute__((used)) static struct opa_vnic_adapter *vema_add_vport(struct opa_vnic_vema_port *port,
					       u8 vport_num)
{
	struct opa_vnic_ctrl_port *cport = port->cport;
	struct opa_vnic_adapter *adapter;

	adapter = opa_vnic_add_netdev(cport->ibdev, port->port_num, vport_num);
	if (!IS_ERR(adapter)) {
		int rc;

		adapter->cport = cport;
		rc = idr_alloc(&port->vport_idr, adapter, vport_num,
			       vport_num + 1, GFP_NOWAIT);
		if (rc < 0) {
			opa_vnic_rem_netdev(adapter);
			adapter = ERR_PTR(rc);
		}
	}

	return adapter;
}