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
struct opa_vnic_vema_port {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;
struct opa_vnic_vema_mad {TYPE_1__ mad_hdr; scalar_t__ data; } ;
struct opa_vnic_adapter {int dummy; } ;
struct opa_veswport_summary_counters {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPA_VNIC_INVAL_ATTR ; 
 int /*<<< orphan*/  opa_vnic_get_summary_counters (struct opa_vnic_adapter*,struct opa_veswport_summary_counters*) ; 
 struct opa_vnic_adapter* vema_get_vport_adapter (struct opa_vnic_vema_mad*,struct opa_vnic_vema_port*) ; 

__attribute__((used)) static void vema_get_summary_counters(struct opa_vnic_vema_port *port,
				      struct opa_vnic_vema_mad *recvd_mad,
				      struct opa_vnic_vema_mad *rsp_mad)
{
	struct opa_veswport_summary_counters *cntrs;
	struct opa_vnic_adapter *adapter;

	adapter = vema_get_vport_adapter(recvd_mad, port);
	if (adapter) {
		cntrs = (struct opa_veswport_summary_counters *)rsp_mad->data;
		opa_vnic_get_summary_counters(adapter, cntrs);
	} else {
		rsp_mad->mad_hdr.status = OPA_VNIC_INVAL_ATTR;
	}
}