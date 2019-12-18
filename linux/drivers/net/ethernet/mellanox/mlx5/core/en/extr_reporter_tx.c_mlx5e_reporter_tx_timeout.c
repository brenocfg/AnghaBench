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
struct TYPE_6__ {int cqn; } ;
struct TYPE_7__ {TYPE_2__ mcq; } ;
struct mlx5e_txqsq {int sqn; int cc; int pc; TYPE_4__* txq; TYPE_3__ cq; TYPE_1__* channel; } ;
struct mlx5e_priv {int /*<<< orphan*/  tx_reporter; } ;
struct mlx5e_err_ctx {int /*<<< orphan*/  recover; struct mlx5e_txqsq* ctx; } ;
struct TYPE_8__ {scalar_t__ trans_start; } ;
struct TYPE_5__ {int ix; struct mlx5e_priv* priv; } ;

/* Variables and functions */
 int MLX5E_REPORTER_PER_Q_MAX_LEN ; 
 scalar_t__ jiffies ; 
 int jiffies_to_usecs (scalar_t__) ; 
 int mlx5e_health_report (struct mlx5e_priv*,int /*<<< orphan*/ ,char*,struct mlx5e_err_ctx*) ; 
 int /*<<< orphan*/  mlx5e_tx_reporter_timeout_recover ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int,int,int) ; 

int mlx5e_reporter_tx_timeout(struct mlx5e_txqsq *sq)
{
	struct mlx5e_priv *priv = sq->channel->priv;
	char err_str[MLX5E_REPORTER_PER_Q_MAX_LEN];
	struct mlx5e_err_ctx err_ctx;

	err_ctx.ctx = sq;
	err_ctx.recover = mlx5e_tx_reporter_timeout_recover;
	sprintf(err_str,
		"TX timeout on queue: %d, SQ: 0x%x, CQ: 0x%x, SQ Cons: 0x%x SQ Prod: 0x%x, usecs since last trans: %u\n",
		sq->channel->ix, sq->sqn, sq->cq.mcq.cqn, sq->cc, sq->pc,
		jiffies_to_usecs(jiffies - sq->txq->trans_start));

	return mlx5e_health_report(priv, priv->tx_reporter, err_str, &err_ctx);
}