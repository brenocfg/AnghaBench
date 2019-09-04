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
struct pvrdma_dev {TYPE_2__* dsr; } ;
struct ib_port_immutable {int /*<<< orphan*/  max_mad_size; int /*<<< orphan*/  gid_tbl_len; int /*<<< orphan*/  pkey_tbl_len; int /*<<< orphan*/  core_cap_flags; } ;
struct ib_port_attr {int /*<<< orphan*/  gid_tbl_len; int /*<<< orphan*/  pkey_tbl_len; } ;
struct ib_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ gid_types; } ;
struct TYPE_4__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_MGMT_MAD_SIZE ; 
 scalar_t__ PVRDMA_GID_TYPE_FLAG_ROCE_V1 ; 
 scalar_t__ PVRDMA_GID_TYPE_FLAG_ROCE_V2 ; 
 int /*<<< orphan*/  RDMA_CORE_PORT_IBA_ROCE ; 
 int /*<<< orphan*/  RDMA_CORE_PORT_IBA_ROCE_UDP_ENCAP ; 
 int ib_query_port (struct ib_device*,int /*<<< orphan*/ ,struct ib_port_attr*) ; 
 struct pvrdma_dev* to_vdev (struct ib_device*) ; 

__attribute__((used)) static int pvrdma_port_immutable(struct ib_device *ibdev, u8 port_num,
				 struct ib_port_immutable *immutable)
{
	struct pvrdma_dev *dev = to_vdev(ibdev);
	struct ib_port_attr attr;
	int err;

	if (dev->dsr->caps.gid_types == PVRDMA_GID_TYPE_FLAG_ROCE_V1)
		immutable->core_cap_flags |= RDMA_CORE_PORT_IBA_ROCE;
	else if (dev->dsr->caps.gid_types == PVRDMA_GID_TYPE_FLAG_ROCE_V2)
		immutable->core_cap_flags |= RDMA_CORE_PORT_IBA_ROCE_UDP_ENCAP;

	err = ib_query_port(ibdev, port_num, &attr);
	if (err)
		return err;

	immutable->pkey_tbl_len = attr.pkey_tbl_len;
	immutable->gid_tbl_len = attr.gid_tbl_len;
	immutable->max_mad_size = IB_MGMT_MAD_SIZE;
	return 0;
}