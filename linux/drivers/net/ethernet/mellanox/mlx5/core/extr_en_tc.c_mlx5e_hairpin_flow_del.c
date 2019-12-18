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
struct mlx5e_tc_flow {TYPE_1__* hpe; int /*<<< orphan*/  hairpin; } ;
struct mlx5e_priv {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flows_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_hairpin_put (struct mlx5e_priv*,TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5e_hairpin_flow_del(struct mlx5e_priv *priv,
				   struct mlx5e_tc_flow *flow)
{
	/* flow wasn't fully initialized */
	if (!flow->hpe)
		return;

	spin_lock(&flow->hpe->flows_lock);
	list_del(&flow->hairpin);
	spin_unlock(&flow->hpe->flows_lock);

	mlx5e_hairpin_put(priv, flow->hpe);
	flow->hpe = NULL;
}