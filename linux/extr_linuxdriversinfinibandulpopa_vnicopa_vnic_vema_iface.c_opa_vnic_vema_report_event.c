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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/  encap_slid; int /*<<< orphan*/  port_num; } ;
struct TYPE_4__ {int /*<<< orphan*/  vesw_id; int /*<<< orphan*/  fabric_id; } ;
struct __opa_veswport_info {TYPE_1__ vport; TYPE_2__ vesw; } ;
struct opa_vnic_adapter {int /*<<< orphan*/  vport_num; int /*<<< orphan*/  port_num; struct __opa_veswport_info info; } ;
struct __opa_veswport_trap {int /*<<< orphan*/  opcode; int /*<<< orphan*/  veswportindex; int /*<<< orphan*/  opaportnum; int /*<<< orphan*/  veswportnum; int /*<<< orphan*/  veswid; int /*<<< orphan*/  fabric_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  opa_vnic_vema_send_trap (struct opa_vnic_adapter*,struct __opa_veswport_trap*,int /*<<< orphan*/ ) ; 

void opa_vnic_vema_report_event(struct opa_vnic_adapter *adapter, u8 event)
{
	struct __opa_veswport_info *info = &adapter->info;
	struct __opa_veswport_trap trap_data;

	trap_data.fabric_id = info->vesw.fabric_id;
	trap_data.veswid = info->vesw.vesw_id;
	trap_data.veswportnum = info->vport.port_num;
	trap_data.opaportnum = adapter->port_num;
	trap_data.veswportindex = adapter->vport_num;
	trap_data.opcode = event;

	opa_vnic_vema_send_trap(adapter, &trap_data, info->vport.encap_slid);
}