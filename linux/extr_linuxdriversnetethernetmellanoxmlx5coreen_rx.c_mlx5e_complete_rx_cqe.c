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
typedef  scalar_t__ u32 ;
struct sk_buff {int dummy; } ;
struct mlx5e_rq_stats {int /*<<< orphan*/  bytes; int /*<<< orphan*/  packets; } ;
struct mlx5e_rq {struct mlx5e_rq_stats* stats; } ;
struct mlx5_cqe64 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_build_rx_skb (struct mlx5_cqe64*,scalar_t__,struct mlx5e_rq*,struct sk_buff*) ; 

__attribute__((used)) static inline void mlx5e_complete_rx_cqe(struct mlx5e_rq *rq,
					 struct mlx5_cqe64 *cqe,
					 u32 cqe_bcnt,
					 struct sk_buff *skb)
{
	struct mlx5e_rq_stats *stats = rq->stats;

	stats->packets++;
	stats->bytes += cqe_bcnt;
	mlx5e_build_rx_skb(cqe, cqe_bcnt, rq, skb);
}