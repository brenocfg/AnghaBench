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
struct TYPE_4__ {int /*<<< orphan*/  work; struct mlx5_hv_vhca_agent* agent; int /*<<< orphan*/  buf; } ;
struct mlx5e_priv {TYPE_2__ stats_agent; int /*<<< orphan*/  netdev; TYPE_1__* mdev; } ;
struct mlx5_hv_vhca_agent {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  hv_vhca; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct mlx5_hv_vhca_agent*) ; 
 int IS_ERR_OR_NULL (struct mlx5_hv_vhca_agent*) ; 
 int /*<<< orphan*/  MLX5_HV_VHCA_AGENT_STATS ; 
 int /*<<< orphan*/  PTR_ERR (struct mlx5_hv_vhca_agent*) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvzalloc (int,int /*<<< orphan*/ ) ; 
 struct mlx5_hv_vhca_agent* mlx5_hv_vhca_agent_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mlx5e_priv*) ; 
 int mlx5e_hv_vhca_stats_buf_size (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_hv_vhca_stats_cleanup ; 
 int /*<<< orphan*/  mlx5e_hv_vhca_stats_control ; 
 int /*<<< orphan*/  mlx5e_hv_vhca_stats_work ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int mlx5e_hv_vhca_stats_create(struct mlx5e_priv *priv)
{
	int buf_len = mlx5e_hv_vhca_stats_buf_size(priv);
	struct mlx5_hv_vhca_agent *agent;

	priv->stats_agent.buf = kvzalloc(buf_len, GFP_KERNEL);
	if (!priv->stats_agent.buf)
		return -ENOMEM;

	agent = mlx5_hv_vhca_agent_create(priv->mdev->hv_vhca,
					  MLX5_HV_VHCA_AGENT_STATS,
					  mlx5e_hv_vhca_stats_control, NULL,
					  mlx5e_hv_vhca_stats_cleanup,
					  priv);

	if (IS_ERR_OR_NULL(agent)) {
		if (IS_ERR(agent))
			netdev_warn(priv->netdev,
				    "Failed to create hv vhca stats agent, err = %ld\n",
				    PTR_ERR(agent));

		kvfree(priv->stats_agent.buf);
		return IS_ERR_OR_NULL(agent);
	}

	priv->stats_agent.agent = agent;
	INIT_DELAYED_WORK(&priv->stats_agent.work, mlx5e_hv_vhca_stats_work);

	return 0;
}