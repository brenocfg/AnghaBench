#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_10__ {int sgid_index; struct ib_gid_attr* sgid_attr; } ;
struct TYPE_9__ {int /*<<< orphan*/  dmac; } ;
struct rdma_ah_attr {TYPE_2__ grh; TYPE_1__ roce; } ;
struct mlx4_ib_dev {struct mlx4_dev* dev; } ;
struct TYPE_14__ {int gid_index; int stat_rate; int /*<<< orphan*/  sl_tclass_flowlabel; struct in6_addr* dgid; int /*<<< orphan*/  hop_limit; void* vlan; int /*<<< orphan*/  port_pd; int /*<<< orphan*/ * s_mac; struct in6_addr* mac; } ;
struct TYPE_12__ {void* dlid; } ;
struct TYPE_15__ {TYPE_6__ eth; TYPE_4__ ib; } ;
struct mlx4_ib_ah {TYPE_7__ av; } ;
struct TYPE_11__ {int stat_rate_support; } ;
struct mlx4_dev {TYPE_3__ caps; } ;
struct in6_addr {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/  raw; } ;
struct ib_global_route {int traffic_class; int flow_label; TYPE_5__ dgid; int /*<<< orphan*/  hop_limit; } ;
struct ib_gid_attr {int dummy; } ;
struct ib_ah {int /*<<< orphan*/  pd; int /*<<< orphan*/  device; } ;
typedef  int /*<<< orphan*/  in6 ;
struct TYPE_16__ {int pdn; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int IB_RATE_2_5_GBPS ; 
 int MLX4_STAT_RATE_OFFSET ; 
 void* cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct in6_addr*,int /*<<< orphan*/ ,int) ; 
 int mlx4_ib_gid_index_to_real_index (struct mlx4_ib_dev*,struct ib_gid_attr const*) ; 
 int rdma_ah_get_port_num (struct rdma_ah_attr*) ; 
 int rdma_ah_get_sl (struct rdma_ah_attr*) ; 
 int rdma_ah_get_static_rate (struct rdma_ah_attr*) ; 
 struct ib_global_route* rdma_ah_read_grh (struct rdma_ah_attr*) ; 
 scalar_t__ rdma_is_multicast_addr (struct in6_addr*) ; 
 int rdma_read_gid_l2_fields (struct ib_gid_attr const*,int*,int /*<<< orphan*/ *) ; 
 struct mlx4_ib_ah* to_mah (struct ib_ah*) ; 
 struct mlx4_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 TYPE_8__* to_mpd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_iboe_ah(struct ib_ah *ib_ah, struct rdma_ah_attr *ah_attr)
{
	struct mlx4_ib_dev *ibdev = to_mdev(ib_ah->device);
	struct mlx4_ib_ah *ah = to_mah(ib_ah);
	const struct ib_gid_attr *gid_attr;
	struct mlx4_dev *dev = ibdev->dev;
	int is_mcast = 0;
	struct in6_addr in6;
	u16 vlan_tag = 0xffff;
	const struct ib_global_route *grh = rdma_ah_read_grh(ah_attr);
	int ret;

	memcpy(&in6, grh->dgid.raw, sizeof(in6));
	if (rdma_is_multicast_addr(&in6))
		is_mcast = 1;

	memcpy(ah->av.eth.mac, ah_attr->roce.dmac, ETH_ALEN);
	eth_zero_addr(ah->av.eth.s_mac);

	/*
	 * If sgid_attr is NULL we are being called by mlx4_ib_create_ah_slave
	 * and we are directly creating an AV for a slave's gid_index.
	 */
	gid_attr = ah_attr->grh.sgid_attr;
	if (gid_attr) {
		ret = rdma_read_gid_l2_fields(gid_attr, &vlan_tag,
					      &ah->av.eth.s_mac[0]);
		if (ret)
			return ret;

		ret = mlx4_ib_gid_index_to_real_index(ibdev, gid_attr);
		if (ret < 0)
			return ret;
		ah->av.eth.gid_index = ret;
	} else {
		/* mlx4_ib_create_ah_slave fills in the s_mac and the vlan */
		ah->av.eth.gid_index = ah_attr->grh.sgid_index;
	}

	if (vlan_tag < 0x1000)
		vlan_tag |= (rdma_ah_get_sl(ah_attr) & 7) << 13;
	ah->av.eth.port_pd = cpu_to_be32(to_mpd(ib_ah->pd)->pdn |
					 (rdma_ah_get_port_num(ah_attr) << 24));
	ah->av.eth.vlan = cpu_to_be16(vlan_tag);
	ah->av.eth.hop_limit = grh->hop_limit;
	if (rdma_ah_get_static_rate(ah_attr)) {
		ah->av.eth.stat_rate = rdma_ah_get_static_rate(ah_attr) +
					MLX4_STAT_RATE_OFFSET;
		while (ah->av.eth.stat_rate > IB_RATE_2_5_GBPS + MLX4_STAT_RATE_OFFSET &&
		       !(1 << ah->av.eth.stat_rate & dev->caps.stat_rate_support))
			--ah->av.eth.stat_rate;
	}
	ah->av.eth.sl_tclass_flowlabel |=
			cpu_to_be32((grh->traffic_class << 20) |
				    grh->flow_label);
	/*
	 * HW requires multicast LID so we just choose one.
	 */
	if (is_mcast)
		ah->av.ib.dlid = cpu_to_be16(0xc000);

	memcpy(ah->av.eth.dgid, grh->dgid.raw, 16);
	ah->av.eth.sl_tclass_flowlabel |= cpu_to_be32(rdma_ah_get_sl(ah_attr)
						      << 29);
	return 0;
}