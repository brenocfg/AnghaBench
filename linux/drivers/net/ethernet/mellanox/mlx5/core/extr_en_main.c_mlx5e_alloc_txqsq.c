#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  work; } ;
struct mlx5_wq_cyc {int /*<<< orphan*/ * db; } ;
struct mlx5e_txqsq {size_t ch_ix; int txq_ix; int /*<<< orphan*/  wq_ctrl; TYPE_5__ dim; int /*<<< orphan*/  stop_room; int /*<<< orphan*/  state; int /*<<< orphan*/  recover_work; int /*<<< orphan*/ * stats; int /*<<< orphan*/  hw_mtu; int /*<<< orphan*/  min_inline_mode; int /*<<< orphan*/  uar_map; struct mlx5e_channel* channel; int /*<<< orphan*/  mkey_be; int /*<<< orphan*/ * clock; int /*<<< orphan*/  tstamp; int /*<<< orphan*/  pdev; struct mlx5_wq_cyc wq; } ;
struct TYPE_14__ {int /*<<< orphan*/  db_numa_node; } ;
struct mlx5e_sq_param {TYPE_7__ wq; int /*<<< orphan*/  sqc; } ;
struct TYPE_13__ {int /*<<< orphan*/  cq_period_mode; } ;
struct mlx5e_params {TYPE_6__ tx_cq_moderation; int /*<<< orphan*/  sw_mtu; int /*<<< orphan*/  tx_min_inline_mode; } ;
struct mlx5e_channel {size_t ix; int /*<<< orphan*/  cpu; TYPE_4__* priv; int /*<<< orphan*/  mkey_be; int /*<<< orphan*/  tstamp; int /*<<< orphan*/  pdev; struct mlx5_core_dev* mdev; } ;
struct TYPE_8__ {int /*<<< orphan*/  map; } ;
struct TYPE_9__ {TYPE_1__ bfreg; } ;
struct mlx5_core_dev {TYPE_2__ mlx5e_res; int /*<<< orphan*/  clock; } ;
struct TYPE_11__ {int /*<<< orphan*/  mdev; TYPE_3__* channel_stats; } ;
struct TYPE_10__ {int /*<<< orphan*/ * sq; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_SKB_FRAGS ; 
 int /*<<< orphan*/  MLX5E_SQ_STATE_IPSEC ; 
 int /*<<< orphan*/  MLX5E_SQ_STATE_TLS ; 
 int /*<<< orphan*/  MLX5E_SQ_STATE_VLAN_NEED_L2_INLINE ; 
 int /*<<< orphan*/  MLX5E_SQ_STOP_ROOM ; 
 scalar_t__ MLX5E_SQ_TLS_ROOM ; 
 int /*<<< orphan*/  MLX5E_SW2HW_MTU (struct mlx5e_params*,int /*<<< orphan*/ ) ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_CAP_ETH (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_IPSEC_DEV (int /*<<< orphan*/ ) ; 
 size_t MLX5_SND_DBR ; 
 int /*<<< orphan*/  TLS_MAX_PAYLOAD_SIZE ; 
 int /*<<< orphan*/  cpu_to_node (int /*<<< orphan*/ ) ; 
 scalar_t__ mlx5_accel_is_tls_device (int /*<<< orphan*/ ) ; 
 int mlx5_wq_cyc_create (struct mlx5_core_dev*,TYPE_7__*,void*,struct mlx5_wq_cyc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_wq_destroy (int /*<<< orphan*/ *) ; 
 int mlx5e_alloc_txqsq_db (struct mlx5e_txqsq*,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx5e_ktls_dumps_num_wqebbs (struct mlx5e_txqsq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_tx_dim_work ; 
 int /*<<< orphan*/  mlx5e_tx_err_cqe_work ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqc ; 
 struct mlx5_wq_cyc* wq ; 
 int /*<<< orphan*/  wqe_vlan_insert ; 

__attribute__((used)) static int mlx5e_alloc_txqsq(struct mlx5e_channel *c,
			     int txq_ix,
			     struct mlx5e_params *params,
			     struct mlx5e_sq_param *param,
			     struct mlx5e_txqsq *sq,
			     int tc)
{
	void *sqc_wq               = MLX5_ADDR_OF(sqc, param->sqc, wq);
	struct mlx5_core_dev *mdev = c->mdev;
	struct mlx5_wq_cyc *wq = &sq->wq;
	int err;

	sq->pdev      = c->pdev;
	sq->tstamp    = c->tstamp;
	sq->clock     = &mdev->clock;
	sq->mkey_be   = c->mkey_be;
	sq->channel   = c;
	sq->ch_ix     = c->ix;
	sq->txq_ix    = txq_ix;
	sq->uar_map   = mdev->mlx5e_res.bfreg.map;
	sq->min_inline_mode = params->tx_min_inline_mode;
	sq->hw_mtu    = MLX5E_SW2HW_MTU(params, params->sw_mtu);
	sq->stats     = &c->priv->channel_stats[c->ix].sq[tc];
	sq->stop_room = MLX5E_SQ_STOP_ROOM;
	INIT_WORK(&sq->recover_work, mlx5e_tx_err_cqe_work);
	if (!MLX5_CAP_ETH(mdev, wqe_vlan_insert))
		set_bit(MLX5E_SQ_STATE_VLAN_NEED_L2_INLINE, &sq->state);
	if (MLX5_IPSEC_DEV(c->priv->mdev))
		set_bit(MLX5E_SQ_STATE_IPSEC, &sq->state);
#ifdef CONFIG_MLX5_EN_TLS
	if (mlx5_accel_is_tls_device(c->priv->mdev)) {
		set_bit(MLX5E_SQ_STATE_TLS, &sq->state);
		sq->stop_room += MLX5E_SQ_TLS_ROOM +
			mlx5e_ktls_dumps_num_wqebbs(sq, MAX_SKB_FRAGS,
						    TLS_MAX_PAYLOAD_SIZE);
	}
#endif

	param->wq.db_numa_node = cpu_to_node(c->cpu);
	err = mlx5_wq_cyc_create(mdev, &param->wq, sqc_wq, wq, &sq->wq_ctrl);
	if (err)
		return err;
	wq->db    = &wq->db[MLX5_SND_DBR];

	err = mlx5e_alloc_txqsq_db(sq, cpu_to_node(c->cpu));
	if (err)
		goto err_sq_wq_destroy;

	INIT_WORK(&sq->dim.work, mlx5e_tx_dim_work);
	sq->dim.mode = params->tx_cq_moderation.cq_period_mode;

	return 0;

err_sq_wq_destroy:
	mlx5_wq_destroy(&sq->wq_ctrl);

	return err;
}