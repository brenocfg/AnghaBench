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
typedef  int /*<<< orphan*/  u8 ;
struct ib_port_immutable {int /*<<< orphan*/  max_mad_size; int /*<<< orphan*/  core_cap_flags; int /*<<< orphan*/  gid_tbl_len; int /*<<< orphan*/  pkey_tbl_len; } ;
struct ib_port_attr {int /*<<< orphan*/  gid_tbl_len; int /*<<< orphan*/  pkey_tbl_len; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IB_MGMT_MAD_SIZE ; 
 int /*<<< orphan*/  RDMA_CORE_CAP_PROT_ROCE_UDP_ENCAP ; 
 int /*<<< orphan*/  RDMA_CORE_PORT_IBA_ROCE ; 
 scalar_t__ bnxt_re_query_port (struct ib_device*,int /*<<< orphan*/ ,struct ib_port_attr*) ; 

int bnxt_re_get_port_immutable(struct ib_device *ibdev, u8 port_num,
			       struct ib_port_immutable *immutable)
{
	struct ib_port_attr port_attr;

	if (bnxt_re_query_port(ibdev, port_num, &port_attr))
		return -EINVAL;

	immutable->pkey_tbl_len = port_attr.pkey_tbl_len;
	immutable->gid_tbl_len = port_attr.gid_tbl_len;
	immutable->core_cap_flags = RDMA_CORE_PORT_IBA_ROCE;
	immutable->core_cap_flags |= RDMA_CORE_CAP_PROT_ROCE_UDP_ENCAP;
	immutable->max_mad_size = IB_MGMT_MAD_SIZE;
	return 0;
}