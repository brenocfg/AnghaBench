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
typedef  int u8 ;
typedef  int u32 ;
struct rdma_ah_attr {int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int gid_table_len; } ;
struct mthca_dev {TYPE_1__ limits; } ;
struct mthca_ah {scalar_t__ type; TYPE_2__* av; } ;
struct ib_ah {int /*<<< orphan*/  type; int /*<<< orphan*/  device; } ;
struct TYPE_4__ {int msg_sr; int g_slid; int gid_index; int /*<<< orphan*/  dgid; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  sl_tclass_flowlabel; int /*<<< orphan*/  dlid; int /*<<< orphan*/  port_pd; } ;

/* Variables and functions */
 int ENOSYS ; 
 scalar_t__ MTHCA_AH_ON_HCA ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct rdma_ah_attr*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mthca_ah_grh_present (struct mthca_ah*) ; 
 int /*<<< orphan*/  mthca_rate_to_ib (struct mthca_dev*,int,int) ; 
 int /*<<< orphan*/  rdma_ah_set_dgid_raw (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_dlid (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_grh (struct rdma_ah_attr*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdma_ah_set_path_bits (struct rdma_ah_attr*,int) ; 
 int /*<<< orphan*/  rdma_ah_set_port_num (struct rdma_ah_attr*,int) ; 
 int /*<<< orphan*/  rdma_ah_set_sl (struct rdma_ah_attr*,int) ; 
 int /*<<< orphan*/  rdma_ah_set_static_rate (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 struct mthca_ah* to_mah (struct ib_ah*) ; 
 struct mthca_dev* to_mdev (int /*<<< orphan*/ ) ; 

int mthca_ah_query(struct ib_ah *ibah, struct rdma_ah_attr *attr)
{
	struct mthca_ah *ah   = to_mah(ibah);
	struct mthca_dev *dev = to_mdev(ibah->device);
	u8 port_num = be32_to_cpu(ah->av->port_pd) >> 24;

	/* Only implement for MAD and memfree ah for now. */
	if (ah->type == MTHCA_AH_ON_HCA)
		return -ENOSYS;

	memset(attr, 0, sizeof *attr);
	attr->type = ibah->type;
	rdma_ah_set_dlid(attr, be16_to_cpu(ah->av->dlid));
	rdma_ah_set_sl(attr, be32_to_cpu(ah->av->sl_tclass_flowlabel) >> 28);
	rdma_ah_set_port_num(attr, port_num);
	rdma_ah_set_static_rate(attr,
				mthca_rate_to_ib(dev, ah->av->msg_sr & 0x7,
						 port_num));
	rdma_ah_set_path_bits(attr, ah->av->g_slid & 0x7F);
	if (mthca_ah_grh_present(ah)) {
		u32 tc_fl = be32_to_cpu(ah->av->sl_tclass_flowlabel);

		rdma_ah_set_grh(attr, NULL,
				tc_fl & 0xfffff,
				ah->av->gid_index &
				(dev->limits.gid_table_len - 1),
				ah->av->hop_limit,
				(tc_fl >> 20) & 0xff);
		rdma_ah_set_dgid_raw(attr, ah->av->dgid);
	}

	return 0;
}