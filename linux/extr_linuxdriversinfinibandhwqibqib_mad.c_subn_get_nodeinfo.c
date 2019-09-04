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
struct qib_devdata {unsigned int num_pports; int majrev; int minrev; int /*<<< orphan*/  deviceid; TYPE_1__* pport; } ;
struct ib_smp {int /*<<< orphan*/  status; scalar_t__ attr_mod; int /*<<< orphan*/  data; } ;
struct ib_node_info {scalar_t__ port_guid; int base_version; int class_version; int node_type; scalar_t__ node_guid; int local_port_num; int /*<<< orphan*/ * vendor_id; int /*<<< orphan*/  revision; void* device_id; void* partition_cap; int /*<<< orphan*/  sys_guid; int /*<<< orphan*/  num_ports; } ;
struct ib_device {int /*<<< orphan*/  phys_port_cnt; } ;
struct TYPE_2__ {scalar_t__ guid; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_SMP_INVALID_FIELD ; 
 int /*<<< orphan*/  QIB_SRC_OUI_1 ; 
 int /*<<< orphan*/  QIB_SRC_OUI_2 ; 
 int /*<<< orphan*/  QIB_SRC_OUI_3 ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 struct qib_devdata* dd_from_ibdev (struct ib_device*) ; 
 int /*<<< orphan*/  ib_qib_sys_image_guid ; 
 int /*<<< orphan*/  qib_get_npkeys (struct qib_devdata*) ; 
 int reply (struct ib_smp*) ; 

__attribute__((used)) static int subn_get_nodeinfo(struct ib_smp *smp, struct ib_device *ibdev,
			     u8 port)
{
	struct ib_node_info *nip = (struct ib_node_info *)&smp->data;
	struct qib_devdata *dd = dd_from_ibdev(ibdev);
	u32 majrev, minrev;
	unsigned pidx = port - 1; /* IB number port from 1, hdw from 0 */

	/* GUID 0 is illegal */
	if (smp->attr_mod || pidx >= dd->num_pports ||
	    dd->pport[pidx].guid == 0)
		smp->status |= IB_SMP_INVALID_FIELD;
	else
		nip->port_guid = dd->pport[pidx].guid;

	nip->base_version = 1;
	nip->class_version = 1;
	nip->node_type = 1;     /* channel adapter */
	nip->num_ports = ibdev->phys_port_cnt;
	/* This is already in network order */
	nip->sys_guid = ib_qib_sys_image_guid;
	nip->node_guid = dd->pport->guid; /* Use first-port GUID as node */
	nip->partition_cap = cpu_to_be16(qib_get_npkeys(dd));
	nip->device_id = cpu_to_be16(dd->deviceid);
	majrev = dd->majrev;
	minrev = dd->minrev;
	nip->revision = cpu_to_be32((majrev << 16) | minrev);
	nip->local_port_num = port;
	nip->vendor_id[0] = QIB_SRC_OUI_1;
	nip->vendor_id[1] = QIB_SRC_OUI_2;
	nip->vendor_id[2] = QIB_SRC_OUI_3;

	return reply(smp);
}