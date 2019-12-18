#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct mlx5e_wqe_frag_info {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  napi; } ;
struct mlx5_wq_cyc {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  skb_from_cqe; struct mlx5_wq_cyc wq; } ;
struct mlx5e_rq {TYPE_3__ cq; int /*<<< orphan*/  flags; TYPE_2__ wqe; TYPE_1__* stats; } ;
struct mlx5_cqe64 {int /*<<< orphan*/  byte_cnt; int /*<<< orphan*/  wqe_counter; } ;
struct TYPE_4__ {int /*<<< orphan*/  wqe_err; } ;

/* Variables and functions */
 struct sk_buff* INDIRECT_CALL_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlx5e_rq*,struct mlx5_cqe64*,struct mlx5e_wqe_frag_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5E_RQ_FLAG_XDP_XMIT ; 
 int /*<<< orphan*/  MLX5E_RX_ERR_CQE (struct mlx5_cqe64*) ; 
 scalar_t__ __test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct mlx5e_wqe_frag_info* get_frag (struct mlx5e_rq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_wq_cyc_ctr2ix (struct mlx5_wq_cyc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_wq_cyc_pop (struct mlx5_wq_cyc*) ; 
 int /*<<< orphan*/  mlx5e_complete_rx_cqe (struct mlx5e_rq*,struct mlx5_cqe64*,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  mlx5e_free_rx_wqe (struct mlx5e_rq*,struct mlx5e_wqe_frag_info*,int) ; 
 int /*<<< orphan*/  mlx5e_skb_from_cqe_linear ; 
 int /*<<< orphan*/  mlx5e_skb_from_cqe_nonlinear ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  trigger_report (struct mlx5e_rq*,struct mlx5_cqe64*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

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

	if (unlikely(MLX5E_RX_ERR_CQE(cqe))) {
		trigger_report(rq, cqe);
		rq->stats->wqe_err++;
		goto free_wqe;
	}

	skb = INDIRECT_CALL_2(rq->wqe.skb_from_cqe,
			      mlx5e_skb_from_cqe_linear,
			      mlx5e_skb_from_cqe_nonlinear,
			      rq, cqe, wi, cqe_bcnt);
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