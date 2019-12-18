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
struct ib_port_immutable {int /*<<< orphan*/  core_cap_flags; int /*<<< orphan*/  max_mad_size; int /*<<< orphan*/  gid_tbl_len; int /*<<< orphan*/  pkey_tbl_len; } ;
struct ib_port_attr {int /*<<< orphan*/  gid_tbl_len; int /*<<< orphan*/  pkey_tbl_len; } ;
struct ib_device {int dummy; } ;
struct TYPE_3__ {int flags; } ;
struct TYPE_4__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int HNS_ROCE_CAP_FLAG_ROCE_V1_V2 ; 
 int /*<<< orphan*/  IB_MGMT_MAD_SIZE ; 
 int /*<<< orphan*/  RDMA_CORE_PORT_IBA_ROCE ; 
 int /*<<< orphan*/  RDMA_CORE_PORT_IBA_ROCE_UDP_ENCAP ; 
 int ib_query_port (struct ib_device*,int /*<<< orphan*/ ,struct ib_port_attr*) ; 
 TYPE_2__* to_hr_dev (struct ib_device*) ; 

__attribute__((used)) static int hns_roce_port_immutable(struct ib_device *ib_dev, u8 port_num,
				   struct ib_port_immutable *immutable)
{
	struct ib_port_attr attr;
	int ret;

	ret = ib_query_port(ib_dev, port_num, &attr);
	if (ret)
		return ret;

	immutable->pkey_tbl_len = attr.pkey_tbl_len;
	immutable->gid_tbl_len = attr.gid_tbl_len;

	immutable->max_mad_size = IB_MGMT_MAD_SIZE;
	immutable->core_cap_flags = RDMA_CORE_PORT_IBA_ROCE;
	if (to_hr_dev(ib_dev)->caps.flags & HNS_ROCE_CAP_FLAG_ROCE_V1_V2)
		immutable->core_cap_flags |= RDMA_CORE_PORT_IBA_ROCE_UDP_ENCAP;

	return 0;
}