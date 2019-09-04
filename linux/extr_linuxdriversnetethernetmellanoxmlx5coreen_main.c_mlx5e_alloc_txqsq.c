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
struct TYPE_14__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  work; } ;
struct TYPE_12__ {int /*<<< orphan*/  recover_work; } ;
struct mlx5_wq_cyc {int /*<<< orphan*/ * db; } ;
struct mlx5e_txqsq {int txq_ix; int /*<<< orphan*/  wq_ctrl; TYPE_6__ dim; int /*<<< orphan*/  state; TYPE_4__ recover; int /*<<< orphan*/ * stats; int /*<<< orphan*/  min_inline_mode; int /*<<< orphan*/  uar_map; struct mlx5e_channel* channel; int /*<<< orphan*/  mkey_be; int /*<<< orphan*/ * clock; int /*<<< orphan*/  tstamp; int /*<<< orphan*/  pdev; struct mlx5_wq_cyc wq; } ;
struct TYPE_16__ {int /*<<< orphan*/  db_numa_node; } ;
struct mlx5e_sq_param {TYPE_8__ wq; int /*<<< orphan*/  sqc; } ;
struct TYPE_15__ {int /*<<< orphan*/  cq_period_mode; } ;
struct mlx5e_params {TYPE_7__ tx_cq_moderation; int /*<<< orphan*/  tx_min_inline_mode; } ;
struct mlx5e_channel {size_t ix; int /*<<< orphan*/  cpu; TYPE_5__* priv; int /*<<< orphan*/  mkey_be; int /*<<< orphan*/  tstamp; int /*<<< orphan*/  pdev; struct mlx5_core_dev* mdev; } ;
struct TYPE_9__ {int /*<<< orphan*/  map; } ;
struct TYPE_10__ {TYPE_1__ bfreg; } ;
struct mlx5_core_dev {TYPE_2__ mlx5e_res; int /*<<< orphan*/  clock; } ;
struct TYPE_13__ {int /*<<< orphan*/  mdev; TYPE_3__* channel_stats; } ;
struct TYPE_11__ {int /*<<< orphan*/ * sq; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5E_SQ_STATE_IPSEC ; 
 int /*<<< orphan*/  MLX5E_SQ_STATE_TLS ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_IPSEC_DEV (int /*<<< orphan*/ ) ; 
 size_t MLX5_SND_DBR ; 
 int /*<<< orphan*/  cpu_to_node (int /*<<< orphan*/ ) ; 
 scalar_t__ mlx5_accel_is_tls_device (int /*<<< orphan*/ ) ; 
 int mlx5_wq_cyc_create (struct mlx5_core_dev*,TYPE_8__*,void*,struct mlx5_wq_cyc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_wq_destroy (int /*<<< orphan*/ *) ; 
 int mlx5e_alloc_txqsq_db (struct mlx5e_txqsq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_sq_recover ; 
 int /*<<< orphan*/  mlx5e_tx_dim_work ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqc ; 
 struct mlx5_wq_cyc* wq ; 

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
	sq->txq_ix    = txq_ix;
	sq->uar_map   = mdev->mlx5e_res.bfreg.map;
	sq->min_inline_mode = params->tx_min_inline_mode;
	sq->stats     = &c->priv->channel_stats[c->ix].sq[tc];
	INIT_WORK(&sq->recover.recover_work, mlx5e_sq_recover);
	if (MLX5_IPSEC_DEV(c->priv->mdev))
		set_bit(MLX5E_SQ_STATE_IPSEC, &sq->state);
	if (mlx5_accel_is_tls_device(c->priv->mdev))
		set_bit(MLX5E_SQ_STATE_TLS, &sq->state);

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