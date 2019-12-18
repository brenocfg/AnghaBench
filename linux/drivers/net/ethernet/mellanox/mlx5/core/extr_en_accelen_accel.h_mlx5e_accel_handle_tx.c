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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct mlx5e_txqsq {int /*<<< orphan*/  state; } ;
struct mlx5e_tx_wqe {int dummy; } ;
struct TYPE_2__ {int gso_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_SQ_STATE_IPSEC ; 
 int /*<<< orphan*/  MLX5E_SQ_STATE_TLS ; 
 int SKB_GSO_UDP_L4 ; 
 struct sk_buff* mlx5e_ipsec_handle_tx_skb (struct net_device*,struct mlx5e_tx_wqe*,struct sk_buff*) ; 
 struct sk_buff* mlx5e_tls_handle_tx_skb (struct net_device*,struct mlx5e_txqsq*,struct sk_buff*,struct mlx5e_tx_wqe**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_udp_gso_handle_tx_skb (struct sk_buff*) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline struct sk_buff *
mlx5e_accel_handle_tx(struct sk_buff *skb,
		      struct mlx5e_txqsq *sq,
		      struct net_device *dev,
		      struct mlx5e_tx_wqe **wqe,
		      u16 *pi)
{
#ifdef CONFIG_MLX5_EN_TLS
	if (test_bit(MLX5E_SQ_STATE_TLS, &sq->state)) {
		skb = mlx5e_tls_handle_tx_skb(dev, sq, skb, wqe, pi);
		if (unlikely(!skb))
			return NULL;
	}
#endif

#ifdef CONFIG_MLX5_EN_IPSEC
	if (test_bit(MLX5E_SQ_STATE_IPSEC, &sq->state)) {
		skb = mlx5e_ipsec_handle_tx_skb(dev, *wqe, skb);
		if (unlikely(!skb))
			return NULL;
	}
#endif

	if (skb_is_gso(skb) && skb_shinfo(skb)->gso_type & SKB_GSO_UDP_L4)
		mlx5e_udp_gso_handle_tx_skb(skb);

	return skb;
}