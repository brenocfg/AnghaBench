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
typedef  int u8 ;
typedef  int u32 ;
struct opa_smp {int /*<<< orphan*/  status; } ;
struct opa_node_info {int node_type; scalar_t__ node_guid; int local_port_num; int /*<<< orphan*/ * vendor_id; int /*<<< orphan*/  revision; void* device_id; void* partition_cap; int /*<<< orphan*/  system_image_guid; int /*<<< orphan*/  num_ports; int /*<<< orphan*/  class_version; int /*<<< orphan*/  base_version; scalar_t__ port_guid; } ;
struct ib_mad_hdr {int dummy; } ;
struct ib_device {scalar_t__ node_guid; int /*<<< orphan*/  phys_port_cnt; } ;
struct hfi1_devdata {unsigned int num_pports; int /*<<< orphan*/  oui3; int /*<<< orphan*/  oui2; int /*<<< orphan*/  oui1; int /*<<< orphan*/  minrev; TYPE_1__* pcidev; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI1_PORT_GUID_INDEX ; 
 int /*<<< orphan*/  IB_SMP_INVALID_FIELD ; 
 int /*<<< orphan*/  OPA_MGMT_BASE_VERSION ; 
 int /*<<< orphan*/  OPA_SM_CLASS_VERSION ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct hfi1_devdata* dd_from_ibdev (struct ib_device*) ; 
 scalar_t__ get_sguid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfi1_get_npkeys (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  ib_hfi1_sys_image_guid ; 
 int reply (struct ib_mad_hdr*) ; 
 scalar_t__ smp_length_check (int,int) ; 
 int /*<<< orphan*/  to_iport (struct ib_device*,int) ; 

__attribute__((used)) static int __subn_get_opa_nodeinfo(struct opa_smp *smp, u32 am, u8 *data,
				   struct ib_device *ibdev, u8 port,
				   u32 *resp_len, u32 max_len)
{
	struct opa_node_info *ni;
	struct hfi1_devdata *dd = dd_from_ibdev(ibdev);
	unsigned pidx = port - 1; /* IB number port from 1, hw from 0 */

	ni = (struct opa_node_info *)data;

	/* GUID 0 is illegal */
	if (am || pidx >= dd->num_pports || ibdev->node_guid == 0 ||
	    smp_length_check(sizeof(*ni), max_len) ||
	    get_sguid(to_iport(ibdev, port), HFI1_PORT_GUID_INDEX) == 0) {
		smp->status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)smp);
	}

	ni->port_guid = get_sguid(to_iport(ibdev, port), HFI1_PORT_GUID_INDEX);
	ni->base_version = OPA_MGMT_BASE_VERSION;
	ni->class_version = OPA_SM_CLASS_VERSION;
	ni->node_type = 1;     /* channel adapter */
	ni->num_ports = ibdev->phys_port_cnt;
	/* This is already in network order */
	ni->system_image_guid = ib_hfi1_sys_image_guid;
	ni->node_guid = ibdev->node_guid;
	ni->partition_cap = cpu_to_be16(hfi1_get_npkeys(dd));
	ni->device_id = cpu_to_be16(dd->pcidev->device);
	ni->revision = cpu_to_be32(dd->minrev);
	ni->local_port_num = port;
	ni->vendor_id[0] = dd->oui1;
	ni->vendor_id[1] = dd->oui2;
	ni->vendor_id[2] = dd->oui3;

	if (resp_len)
		*resp_len += sizeof(*ni);

	return reply((struct ib_mad_hdr *)smp);
}