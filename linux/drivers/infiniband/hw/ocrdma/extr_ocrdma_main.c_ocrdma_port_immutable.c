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
struct ocrdma_dev {int dummy; } ;
struct ib_port_immutable {int /*<<< orphan*/  max_mad_size; int /*<<< orphan*/  gid_tbl_len; int /*<<< orphan*/  pkey_tbl_len; int /*<<< orphan*/  core_cap_flags; } ;
struct ib_port_attr {int /*<<< orphan*/  gid_tbl_len; int /*<<< orphan*/  pkey_tbl_len; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_MGMT_MAD_SIZE ; 
 int /*<<< orphan*/  RDMA_CORE_CAP_PROT_ROCE_UDP_ENCAP ; 
 int /*<<< orphan*/  RDMA_CORE_PORT_IBA_ROCE ; 
 struct ocrdma_dev* get_ocrdma_dev (struct ib_device*) ; 
 int ib_query_port (struct ib_device*,int /*<<< orphan*/ ,struct ib_port_attr*) ; 
 scalar_t__ ocrdma_is_udp_encap_supported (struct ocrdma_dev*) ; 

__attribute__((used)) static int ocrdma_port_immutable(struct ib_device *ibdev, u8 port_num,
			         struct ib_port_immutable *immutable)
{
	struct ib_port_attr attr;
	struct ocrdma_dev *dev;
	int err;

	dev = get_ocrdma_dev(ibdev);
	immutable->core_cap_flags = RDMA_CORE_PORT_IBA_ROCE;
	if (ocrdma_is_udp_encap_supported(dev))
		immutable->core_cap_flags |= RDMA_CORE_CAP_PROT_ROCE_UDP_ENCAP;

	err = ib_query_port(ibdev, port_num, &attr);
	if (err)
		return err;

	immutable->pkey_tbl_len = attr.pkey_tbl_len;
	immutable->gid_tbl_len = attr.gid_tbl_len;
	immutable->max_mad_size = IB_MGMT_MAD_SIZE;

	return 0;
}