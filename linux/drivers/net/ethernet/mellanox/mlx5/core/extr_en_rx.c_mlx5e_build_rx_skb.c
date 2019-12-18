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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int mark; int /*<<< orphan*/  protocol; int /*<<< orphan*/  mac_len; } ;
struct net_device {int features; } ;
struct mlx5e_rq_stats {int /*<<< orphan*/  removed_vlan_packets; int /*<<< orphan*/  lro_bytes; int /*<<< orphan*/  lro_packets; int /*<<< orphan*/  packets; } ;
struct mlx5e_rq {int /*<<< orphan*/  ix; int /*<<< orphan*/  clock; int /*<<< orphan*/  tstamp; struct net_device* netdev; struct mlx5e_rq_stats* stats; } ;
struct mlx5_cqe64 {int ml_path; int /*<<< orphan*/  sop_drop_qpn; int /*<<< orphan*/  vlan_info; int /*<<< orphan*/  srqn; } ;
struct TYPE_4__ {int /*<<< orphan*/  hwtstamp; } ;
struct TYPE_3__ {int /*<<< orphan*/  gso_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int MLX5E_CE_BIT_MASK ; 
 int MLX5E_TC_FLOW_ID_MASK ; 
 int NETIF_F_RXHASH ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ cqe_has_vlan (struct mlx5_cqe64*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  get_cqe_ts (struct mlx5_cqe64*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mlx5_timecounter_cyc2time (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_enable_ecn (struct mlx5e_rq*,struct sk_buff*) ; 
 int /*<<< orphan*/  mlx5e_handle_csum (struct net_device*,struct mlx5_cqe64*,struct mlx5e_rq*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  mlx5e_lro_update_hdr (struct sk_buff*,struct mlx5_cqe64*,int /*<<< orphan*/ ) ; 
 int mlx5e_rx_hw_stamp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_skb_set_hash (struct mlx5_cqe64*,struct sk_buff*) ; 
 int /*<<< orphan*/  mlx5e_tls_handle_rx_skb (struct net_device*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 TYPE_2__* skb_hwtstamps (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_record_rx_queue (struct sk_buff*,int /*<<< orphan*/ ) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void mlx5e_build_rx_skb(struct mlx5_cqe64 *cqe,
				      u32 cqe_bcnt,
				      struct mlx5e_rq *rq,
				      struct sk_buff *skb)
{
	u8 lro_num_seg = be32_to_cpu(cqe->srqn) >> 24;
	struct mlx5e_rq_stats *stats = rq->stats;
	struct net_device *netdev = rq->netdev;

	skb->mac_len = ETH_HLEN;

#ifdef CONFIG_MLX5_EN_TLS
	mlx5e_tls_handle_rx_skb(netdev, skb, &cqe_bcnt);
#endif

	if (lro_num_seg > 1) {
		mlx5e_lro_update_hdr(skb, cqe, cqe_bcnt);
		skb_shinfo(skb)->gso_size = DIV_ROUND_UP(cqe_bcnt, lro_num_seg);
		/* Subtract one since we already counted this as one
		 * "regular" packet in mlx5e_complete_rx_cqe()
		 */
		stats->packets += lro_num_seg - 1;
		stats->lro_packets++;
		stats->lro_bytes += cqe_bcnt;
	}

	if (unlikely(mlx5e_rx_hw_stamp(rq->tstamp)))
		skb_hwtstamps(skb)->hwtstamp =
				mlx5_timecounter_cyc2time(rq->clock, get_cqe_ts(cqe));

	skb_record_rx_queue(skb, rq->ix);

	if (likely(netdev->features & NETIF_F_RXHASH))
		mlx5e_skb_set_hash(cqe, skb);

	if (cqe_has_vlan(cqe)) {
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
				       be16_to_cpu(cqe->vlan_info));
		stats->removed_vlan_packets++;
	}

	skb->mark = be32_to_cpu(cqe->sop_drop_qpn) & MLX5E_TC_FLOW_ID_MASK;

	mlx5e_handle_csum(netdev, cqe, rq, skb, !!lro_num_seg);
	/* checking CE bit in cqe - MSB in ml_path field */
	if (unlikely(cqe->ml_path & MLX5E_CE_BIT_MASK))
		mlx5e_enable_ecn(rq, skb);

	skb->protocol = eth_type_trans(skb, netdev);
}