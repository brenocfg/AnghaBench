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
typedef  int u32 ;
struct rdma_ah_attr {int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int stat_rate_sl; int /*<<< orphan*/  rlid; int /*<<< orphan*/  rgid; int /*<<< orphan*/  tclass; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  grh_gid_fl; } ;
struct mlx5_ib_ah {TYPE_1__ av; } ;
struct ib_ah {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct rdma_ah_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdma_ah_set_dgid_raw (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_dlid (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_grh (struct rdma_ah_attr*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_sl (struct rdma_ah_attr*,int) ; 
 int /*<<< orphan*/  rdma_ah_set_static_rate (struct rdma_ah_attr*,int) ; 
 struct mlx5_ib_ah* to_mah (struct ib_ah*) ; 

int mlx5_ib_query_ah(struct ib_ah *ibah, struct rdma_ah_attr *ah_attr)
{
	struct mlx5_ib_ah *ah = to_mah(ibah);
	u32 tmp;

	memset(ah_attr, 0, sizeof(*ah_attr));
	ah_attr->type = ibah->type;

	tmp = be32_to_cpu(ah->av.grh_gid_fl);
	if (tmp & (1 << 30)) {
		rdma_ah_set_grh(ah_attr, NULL,
				tmp & 0xfffff,
				(tmp >> 20) & 0xff,
				ah->av.hop_limit,
				ah->av.tclass);
		rdma_ah_set_dgid_raw(ah_attr, ah->av.rgid);
	}
	rdma_ah_set_dlid(ah_attr, be16_to_cpu(ah->av.rlid));
	rdma_ah_set_static_rate(ah_attr, ah->av.stat_rate_sl >> 4);
	rdma_ah_set_sl(ah_attr, ah->av.stat_rate_sl & 0xf);

	return 0;
}