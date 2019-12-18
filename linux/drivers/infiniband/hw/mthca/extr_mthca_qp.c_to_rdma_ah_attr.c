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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct rdma_ah_attr {int /*<<< orphan*/  type; } ;
struct mthca_qp_path {int g_mylmc; int static_rate; int mgid_index; int /*<<< orphan*/  rgid; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  sl_tclass_flowlabel; int /*<<< orphan*/  rlid; int /*<<< orphan*/  port_pkey; } ;
struct TYPE_2__ {scalar_t__ num_ports; int gid_table_len; } ;
struct mthca_dev {TYPE_1__ limits; int /*<<< orphan*/  ib_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct rdma_ah_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mthca_rate_to_ib (struct mthca_dev*,int,scalar_t__) ; 
 int /*<<< orphan*/  rdma_ah_find_type (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  rdma_ah_set_dgid_raw (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_dlid (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_grh (struct rdma_ah_attr*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdma_ah_set_path_bits (struct rdma_ah_attr*,int) ; 
 int /*<<< orphan*/  rdma_ah_set_port_num (struct rdma_ah_attr*,scalar_t__) ; 
 int /*<<< orphan*/  rdma_ah_set_sl (struct rdma_ah_attr*,int) ; 
 int /*<<< orphan*/  rdma_ah_set_static_rate (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void to_rdma_ah_attr(struct mthca_dev *dev,
			    struct rdma_ah_attr *ah_attr,
			    struct mthca_qp_path *path)
{
	u8 port_num = (be32_to_cpu(path->port_pkey) >> 24) & 0x3;

	memset(ah_attr, 0, sizeof(*ah_attr));

	if (port_num == 0 || port_num > dev->limits.num_ports)
		return;
	ah_attr->type = rdma_ah_find_type(&dev->ib_dev, port_num);
	rdma_ah_set_port_num(ah_attr, port_num);

	rdma_ah_set_dlid(ah_attr, be16_to_cpu(path->rlid));
	rdma_ah_set_sl(ah_attr, be32_to_cpu(path->sl_tclass_flowlabel) >> 28);
	rdma_ah_set_path_bits(ah_attr, path->g_mylmc & 0x7f);
	rdma_ah_set_static_rate(ah_attr,
				mthca_rate_to_ib(dev,
						 path->static_rate & 0xf,
						 port_num));
	if (path->g_mylmc & (1 << 7)) {
		u32 tc_fl = be32_to_cpu(path->sl_tclass_flowlabel);

		rdma_ah_set_grh(ah_attr, NULL,
				tc_fl & 0xfffff,
				path->mgid_index &
				(dev->limits.gid_table_len - 1),
				path->hop_limit,
				(tc_fl >> 20) & 0xff);
		rdma_ah_set_dgid_raw(ah_attr, path->rgid);
	}
}