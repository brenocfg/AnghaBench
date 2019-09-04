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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct mlx5e_wqe_frag_info {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  napi; } ;
struct mlx5_wq_cyc {int dummy; } ;
struct TYPE_4__ {struct sk_buff* (* skb_from_cqe ) (struct mlx5e_rq*,struct mlx5_cqe64*,struct mlx5e_wqe_frag_info*,int /*<<< orphan*/ ) ;struct mlx5_wq_cyc wq; } ;
struct mlx5e_rq {TYPE_1__ cq; int /*<<< orphan*/  flags; TYPE_2__ wqe; } ;
struct mlx5_cqe64 {int /*<<< orphan*/  byte_cnt; int /*<<< orphan*/  wqe_counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_RQ_FLAG_XDP_XMIT ; 
 scalar_t__ __test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct mlx5e_wqe_frag_info* get_frag (struct mlx5e_rq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_wq_cyc_ctr2ix (struct mlx5_wq_cyc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_wq_cyc_pop (struct mlx5_wq_cyc*) ; 
 int /*<<< orphan*/  mlx5e_complete_rx_cqe (struct mlx5e_rq*,struct mlx5_cqe64*,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  mlx5e_free_rx_wqe (struct mlx5e_rq*,struct mlx5e_wqe_frag_info*,int) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct sk_buff* stub1 (struct mlx5e_rq*,struct mlx5_cqe64*,struct mlx5e_wqe_frag_info*,int /*<<< orphan*/ ) ; 

void mlx5e_handle_rx_cqe(struct mlx5e_rq *rq, struct mlx5_cqe64 *cqe)
{
	struct mlx5_wq_cyc *wq = &rq->wqe.wq;
	struct mlx5e_wqe_frag_info *wi;
	struct sk_buff *skb;
	u32 cqe_bcnt;
	u16 ci;

	ci       = mlx5_wq_cyc_ctr2ix(wq, be16_to_cpu(cqe->wqe_counter));
	wi       = get_frag(rq, ci);
	cqe_bcnt = be32_to_cpu(cqe->byte_cnt);

	skb = rq->wqe.skb_from_cqe(rq, cqe, wi, cqe_bcnt);
	if (!skb) {
		/* probably for XDP */
		if (__test_and_clear_bit(MLX5E_RQ_FLAG_XDP_XMIT, rq->flags)) {
			/* do not return page to cache,
			 * it will be returned on XDP_TX completion.
			 */
			goto wq_cyc_pop;
		}
		goto free_wqe;
	}

	mlx5e_complete_rx_cqe(rq, cqe, cqe_bcnt, skb);
	napi_gro_receive(rq->cq.napi, skb);

free_wqe:
	mlx5e_free_rx_wqe(rq, wi, true);
wq_cyc_pop:
	mlx5_wq_cyc_pop(wq);
}