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
struct sk_buff {scalar_t__ ip_summed; scalar_t__ encapsulation; } ;
struct mlx5e_txqsq {TYPE_1__* stats; } ;
struct mlx5_wqe_eth_seg {int cs_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  csum_none; int /*<<< orphan*/  csum_partial; int /*<<< orphan*/  csum_partial_inner; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int MLX5_ETH_WQE_L3_CSUM ; 
 int MLX5_ETH_WQE_L3_INNER_CSUM ; 
 int MLX5_ETH_WQE_L4_CSUM ; 
 int MLX5_ETH_WQE_L4_INNER_CSUM ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static inline void
mlx5e_txwqe_build_eseg_csum(struct mlx5e_txqsq *sq, struct sk_buff *skb, struct mlx5_wqe_eth_seg *eseg)
{
	if (likely(skb->ip_summed == CHECKSUM_PARTIAL)) {
		eseg->cs_flags = MLX5_ETH_WQE_L3_CSUM;
		if (skb->encapsulation) {
			eseg->cs_flags |= MLX5_ETH_WQE_L3_INNER_CSUM |
					  MLX5_ETH_WQE_L4_INNER_CSUM;
			sq->stats->csum_partial_inner++;
		} else {
			eseg->cs_flags |= MLX5_ETH_WQE_L4_CSUM;
			sq->stats->csum_partial++;
		}
	} else
		sq->stats->csum_none++;
}