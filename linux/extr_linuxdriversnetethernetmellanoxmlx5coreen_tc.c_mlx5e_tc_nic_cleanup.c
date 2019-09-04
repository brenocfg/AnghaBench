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
struct TYPE_4__ {scalar_t__ notifier_call; } ;
struct mlx5e_tc_table {int /*<<< orphan*/ * t; int /*<<< orphan*/  ht; TYPE_2__ netdevice_nb; } ;
struct TYPE_3__ {struct mlx5e_tc_table tc; } ;
struct mlx5e_priv {TYPE_1__ fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _mlx5e_tc_del_flow ; 
 int /*<<< orphan*/  mlx5_destroy_flow_table (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rhashtable_free_and_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdevice_notifier (TYPE_2__*) ; 

void mlx5e_tc_nic_cleanup(struct mlx5e_priv *priv)
{
	struct mlx5e_tc_table *tc = &priv->fs.tc;

	if (tc->netdevice_nb.notifier_call)
		unregister_netdevice_notifier(&tc->netdevice_nb);

	rhashtable_free_and_destroy(&tc->ht, _mlx5e_tc_del_flow, NULL);

	if (!IS_ERR_OR_NULL(tc->t)) {
		mlx5_destroy_flow_table(tc->t);
		tc->t = NULL;
	}
}