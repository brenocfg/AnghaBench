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
struct TYPE_2__ {int /*<<< orphan*/  buf; int /*<<< orphan*/  agent; } ;
struct mlx5e_priv {TYPE_1__ stats_agent; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_hv_vhca_agent_destroy (int /*<<< orphan*/ ) ; 

void mlx5e_hv_vhca_stats_destroy(struct mlx5e_priv *priv)
{
	if (IS_ERR_OR_NULL(priv->stats_agent.agent))
		return;

	mlx5_hv_vhca_agent_destroy(priv->stats_agent.agent);
	kvfree(priv->stats_agent.buf);
}