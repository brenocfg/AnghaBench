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
struct TYPE_6__ {int /*<<< orphan*/  cqn; } ;
struct TYPE_7__ {TYPE_2__ mcq; } ;
struct mlx5e_xdpsq {scalar_t__ min_inline_mode; int sqn; int /*<<< orphan*/  state; int /*<<< orphan*/  mkey_be; int /*<<< orphan*/  wq; int /*<<< orphan*/  wq_ctrl; TYPE_3__ cq; } ;
struct TYPE_8__ {int /*<<< orphan*/  sz; } ;
struct mlx5_wqe_eth_seg {TYPE_4__ inline_hdr; } ;
struct mlx5_wqe_ctrl_seg {int /*<<< orphan*/  qpn_ds; } ;
struct mlx5e_tx_wqe {struct mlx5_wqe_eth_seg eth; struct mlx5_wqe_ctrl_seg ctrl; } ;
struct mlx5e_sq_param {int dummy; } ;
struct mlx5e_params {int dummy; } ;
struct mlx5e_create_sq_param {int tis_lst_sz; scalar_t__ min_inline_mode; int /*<<< orphan*/ * wq_ctrl; int /*<<< orphan*/  cqn; int /*<<< orphan*/  tisn; } ;
struct mlx5e_channel {int /*<<< orphan*/  mdev; TYPE_1__* priv; } ;
struct mlx5_wqe_data_seg {int /*<<< orphan*/  lkey; } ;
struct TYPE_5__ {int /*<<< orphan*/ * tisn; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_SQ_STATE_ENABLED ; 
 int /*<<< orphan*/  MLX5E_SQ_STATE_REDIRECT ; 
 unsigned int MLX5E_XDP_MIN_INLINE ; 
 unsigned int MLX5E_XDP_TX_DS_COUNT ; 
 scalar_t__ MLX5_INLINE_MODE_NONE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_be16 (unsigned int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int mlx5_wq_cyc_get_size (int /*<<< orphan*/ *) ; 
 struct mlx5e_tx_wqe* mlx5_wq_cyc_get_wqe (int /*<<< orphan*/ *,int) ; 
 int mlx5e_alloc_xdpsq (struct mlx5e_channel*,struct mlx5e_params*,struct mlx5e_sq_param*,struct mlx5e_xdpsq*,int) ; 
 int mlx5e_create_sq_rdy (int /*<<< orphan*/ ,struct mlx5e_sq_param*,struct mlx5e_create_sq_param*,int*) ; 
 int /*<<< orphan*/  mlx5e_free_xdpsq (struct mlx5e_xdpsq*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx5e_open_xdpsq(struct mlx5e_channel *c,
			    struct mlx5e_params *params,
			    struct mlx5e_sq_param *param,
			    struct mlx5e_xdpsq *sq,
			    bool is_redirect)
{
	unsigned int ds_cnt = MLX5E_XDP_TX_DS_COUNT;
	struct mlx5e_create_sq_param csp = {};
	unsigned int inline_hdr_sz = 0;
	int err;
	int i;

	err = mlx5e_alloc_xdpsq(c, params, param, sq, is_redirect);
	if (err)
		return err;

	csp.tis_lst_sz      = 1;
	csp.tisn            = c->priv->tisn[0]; /* tc = 0 */
	csp.cqn             = sq->cq.mcq.cqn;
	csp.wq_ctrl         = &sq->wq_ctrl;
	csp.min_inline_mode = sq->min_inline_mode;
	if (is_redirect)
		set_bit(MLX5E_SQ_STATE_REDIRECT, &sq->state);
	set_bit(MLX5E_SQ_STATE_ENABLED, &sq->state);
	err = mlx5e_create_sq_rdy(c->mdev, param, &csp, &sq->sqn);
	if (err)
		goto err_free_xdpsq;

	if (sq->min_inline_mode != MLX5_INLINE_MODE_NONE) {
		inline_hdr_sz = MLX5E_XDP_MIN_INLINE;
		ds_cnt++;
	}

	/* Pre initialize fixed WQE fields */
	for (i = 0; i < mlx5_wq_cyc_get_size(&sq->wq); i++) {
		struct mlx5e_tx_wqe      *wqe  = mlx5_wq_cyc_get_wqe(&sq->wq, i);
		struct mlx5_wqe_ctrl_seg *cseg = &wqe->ctrl;
		struct mlx5_wqe_eth_seg  *eseg = &wqe->eth;
		struct mlx5_wqe_data_seg *dseg;

		cseg->qpn_ds = cpu_to_be32((sq->sqn << 8) | ds_cnt);
		eseg->inline_hdr.sz = cpu_to_be16(inline_hdr_sz);

		dseg = (struct mlx5_wqe_data_seg *)cseg + (ds_cnt - 1);
		dseg->lkey = sq->mkey_be;
	}

	return 0;

err_free_xdpsq:
	clear_bit(MLX5E_SQ_STATE_ENABLED, &sq->state);
	mlx5e_free_xdpsq(sq);

	return err;
}