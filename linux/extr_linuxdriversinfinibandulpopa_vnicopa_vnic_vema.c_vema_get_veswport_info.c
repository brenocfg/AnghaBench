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
struct opa_vnic_vema_port {int dummy; } ;
struct opa_vnic_vema_mad {scalar_t__ data; } ;
struct opa_vnic_adapter {int dummy; } ;
struct opa_veswport_info {int /*<<< orphan*/  vport; int /*<<< orphan*/  vesw; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct opa_veswport_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  opa_vnic_get_per_veswport_info (struct opa_vnic_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opa_vnic_get_vesw_info (struct opa_vnic_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vema_get_pod_values (struct opa_veswport_info*) ; 
 struct opa_vnic_adapter* vema_get_vport_adapter (struct opa_vnic_vema_mad*,struct opa_vnic_vema_port*) ; 

__attribute__((used)) static void vema_get_veswport_info(struct opa_vnic_vema_port *port,
				   struct opa_vnic_vema_mad *recvd_mad,
				   struct opa_vnic_vema_mad *rsp_mad)
{
	struct opa_veswport_info *port_info =
				  (struct opa_veswport_info *)rsp_mad->data;
	struct opa_vnic_adapter *adapter;

	adapter = vema_get_vport_adapter(recvd_mad, port);
	if (adapter) {
		memset(port_info, 0, sizeof(*port_info));
		opa_vnic_get_vesw_info(adapter, &port_info->vesw);
		opa_vnic_get_per_veswport_info(adapter,
					       &port_info->vport);
	} else {
		vema_get_pod_values(port_info);
	}
}