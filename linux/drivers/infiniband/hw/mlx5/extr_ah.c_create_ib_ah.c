#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_4__* sgid_attr; } ;
struct TYPE_5__ {int /*<<< orphan*/ * dmac; } ;
struct rdma_ah_attr {scalar_t__ type; TYPE_2__ grh; TYPE_1__ roce; } ;
struct mlx5_ib_dev {int dummy; } ;
struct TYPE_7__ {int stat_rate_sl; int fl_mlid; int /*<<< orphan*/  rlid; int /*<<< orphan*/  tclass; int /*<<< orphan*/  udp_sport; int /*<<< orphan*/  rmac; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  grh_gid_fl; int /*<<< orphan*/  rgid; } ;
struct mlx5_ib_ah {TYPE_3__ av; } ;
struct ib_global_route {int flow_label; int sgid_index; int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  dgid; } ;
typedef  enum ib_gid_type { ____Placeholder_ib_gid_type } ib_gid_type ;
struct TYPE_8__ {int gid_type; } ;

/* Variables and functions */
 int IB_AH_GRH ; 
 int IB_GID_TYPE_ROCE_UDP_ENCAP ; 
 int /*<<< orphan*/  MLX5_ECN_ENABLED ; 
 scalar_t__ RDMA_AH_ATTR_TYPE_ROCE ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlx5_get_roce_udp_sport (struct mlx5_ib_dev*,TYPE_4__*) ; 
 int rdma_ah_get_ah_flags (struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  rdma_ah_get_dlid (struct rdma_ah_attr*) ; 
 int rdma_ah_get_path_bits (struct rdma_ah_attr*) ; 
 int rdma_ah_get_sl (struct rdma_ah_attr*) ; 
 int rdma_ah_get_static_rate (struct rdma_ah_attr*) ; 
 struct ib_global_route* rdma_ah_read_grh (struct rdma_ah_attr*) ; 

__attribute__((used)) static void create_ib_ah(struct mlx5_ib_dev *dev, struct mlx5_ib_ah *ah,
			 struct rdma_ah_attr *ah_attr)
{
	enum ib_gid_type gid_type;

	if (rdma_ah_get_ah_flags(ah_attr) & IB_AH_GRH) {
		const struct ib_global_route *grh = rdma_ah_read_grh(ah_attr);

		memcpy(ah->av.rgid, &grh->dgid, 16);
		ah->av.grh_gid_fl = cpu_to_be32(grh->flow_label |
						(1 << 30) |
						grh->sgid_index << 20);
		ah->av.hop_limit = grh->hop_limit;
		ah->av.tclass = grh->traffic_class;
	}

	ah->av.stat_rate_sl = (rdma_ah_get_static_rate(ah_attr) << 4);

	if (ah_attr->type == RDMA_AH_ATTR_TYPE_ROCE) {
		gid_type = ah_attr->grh.sgid_attr->gid_type;

		memcpy(ah->av.rmac, ah_attr->roce.dmac,
		       sizeof(ah_attr->roce.dmac));
		ah->av.udp_sport =
			mlx5_get_roce_udp_sport(dev, ah_attr->grh.sgid_attr);
		ah->av.stat_rate_sl |= (rdma_ah_get_sl(ah_attr) & 0x7) << 1;
		if (gid_type == IB_GID_TYPE_ROCE_UDP_ENCAP)
#define MLX5_ECN_ENABLED BIT(1)
			ah->av.tclass |= MLX5_ECN_ENABLED;
	} else {
		ah->av.rlid = cpu_to_be16(rdma_ah_get_dlid(ah_attr));
		ah->av.fl_mlid = rdma_ah_get_path_bits(ah_attr) & 0x7f;
		ah->av.stat_rate_sl |= (rdma_ah_get_sl(ah_attr) & 0xf);
	}
}