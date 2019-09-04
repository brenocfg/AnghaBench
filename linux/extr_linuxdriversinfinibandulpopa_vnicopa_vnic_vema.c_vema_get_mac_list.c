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
typedef  scalar_t__ u16 ;
struct opa_vnic_vema_port {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;
struct opa_vnic_vema_mad {scalar_t__ data; TYPE_1__ mad_hdr; } ;
struct opa_vnic_adapter {int dummy; } ;
struct opa_veswport_iface_macs {scalar_t__ num_macs_in_msg; int /*<<< orphan*/  start_idx; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 scalar_t__ OPA_EM_ATTR_IFACE_MCAST_MACS ; 
 int OPA_VNIC_EMA_DATA ; 
 int /*<<< orphan*/  OPA_VNIC_INVAL_ATTR ; 
 scalar_t__ cpu_to_be16 (int) ; 
 int /*<<< orphan*/  opa_vnic_query_mcast_macs (struct opa_vnic_adapter*,struct opa_veswport_iface_macs*) ; 
 int /*<<< orphan*/  opa_vnic_query_ucast_macs (struct opa_vnic_adapter*,struct opa_veswport_iface_macs*) ; 
 struct opa_vnic_adapter* vema_get_vport_adapter (struct opa_vnic_vema_mad*,struct opa_vnic_vema_port*) ; 

__attribute__((used)) static void vema_get_mac_list(struct opa_vnic_vema_port *port,
			      struct opa_vnic_vema_mad *recvd_mad,
			      struct opa_vnic_vema_mad *rsp_mad,
			      u16 attr_id)
{
	struct opa_veswport_iface_macs *macs_in, *macs_out;
	int max_entries = (OPA_VNIC_EMA_DATA - sizeof(*macs_out)) / ETH_ALEN;
	struct opa_vnic_adapter *adapter;

	adapter = vema_get_vport_adapter(recvd_mad, port);
	if (!adapter) {
		rsp_mad->mad_hdr.status = OPA_VNIC_INVAL_ATTR;
		return;
	}

	macs_in = (struct opa_veswport_iface_macs *)recvd_mad->data;
	macs_out = (struct opa_veswport_iface_macs *)rsp_mad->data;

	macs_out->start_idx = macs_in->start_idx;
	if (macs_in->num_macs_in_msg)
		macs_out->num_macs_in_msg = macs_in->num_macs_in_msg;
	else
		macs_out->num_macs_in_msg = cpu_to_be16(max_entries);

	if (attr_id == OPA_EM_ATTR_IFACE_MCAST_MACS)
		opa_vnic_query_mcast_macs(adapter, macs_out);
	else
		opa_vnic_query_ucast_macs(adapter, macs_out);
}