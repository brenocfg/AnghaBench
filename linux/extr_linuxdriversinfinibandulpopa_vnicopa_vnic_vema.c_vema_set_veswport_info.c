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
typedef  int /*<<< orphan*/  u8 ;
struct opa_vnic_vema_port {struct opa_vnic_ctrl_port* cport; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;
struct opa_vnic_vema_mad {TYPE_1__ mad_hdr; scalar_t__ data; } ;
struct opa_vnic_ctrl_port {int dummy; } ;
struct opa_vnic_adapter {int dummy; } ;
struct opa_veswport_info {int /*<<< orphan*/  vport; int /*<<< orphan*/  vesw; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct opa_vnic_adapter*) ; 
 int /*<<< orphan*/  OPA_VNIC_INVAL_ATTR ; 
 int /*<<< orphan*/  PTR_ERR (struct opa_vnic_adapter*) ; 
 int /*<<< orphan*/  c_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opa_vnic_process_vema_config (struct opa_vnic_adapter*) ; 
 int /*<<< orphan*/  opa_vnic_set_per_veswport_info (struct opa_vnic_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opa_vnic_set_vesw_info (struct opa_vnic_adapter*,int /*<<< orphan*/ *) ; 
 struct opa_vnic_adapter* vema_add_vport (struct opa_vnic_vema_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vema_get_veswport_info (struct opa_vnic_vema_port*,struct opa_vnic_vema_mad*,struct opa_vnic_vema_mad*) ; 
 struct opa_vnic_adapter* vema_get_vport_adapter (struct opa_vnic_vema_mad*,struct opa_vnic_vema_port*) ; 
 int /*<<< orphan*/  vema_get_vport_num (struct opa_vnic_vema_mad*) ; 

__attribute__((used)) static void vema_set_veswport_info(struct opa_vnic_vema_port *port,
				   struct opa_vnic_vema_mad *recvd_mad,
				   struct opa_vnic_vema_mad *rsp_mad)
{
	struct opa_vnic_ctrl_port *cport = port->cport;
	struct opa_veswport_info *port_info;
	struct opa_vnic_adapter *adapter;
	u8 vport_num;

	vport_num = vema_get_vport_num(recvd_mad);

	adapter = vema_get_vport_adapter(recvd_mad, port);
	if (!adapter) {
		adapter = vema_add_vport(port, vport_num);
		if (IS_ERR(adapter)) {
			c_err("failed to add vport %d: %ld\n",
			      vport_num, PTR_ERR(adapter));
			goto err_exit;
		}
	}

	port_info = (struct opa_veswport_info *)recvd_mad->data;
	opa_vnic_set_vesw_info(adapter, &port_info->vesw);
	opa_vnic_set_per_veswport_info(adapter, &port_info->vport);

	/* Process the new config settings */
	opa_vnic_process_vema_config(adapter);

	vema_get_veswport_info(port, recvd_mad, rsp_mad);
	return;

err_exit:
	rsp_mad->mad_hdr.status = OPA_VNIC_INVAL_ATTR;
}