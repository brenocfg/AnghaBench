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
struct mlxsw_sp_mr_tcam_route {int /*<<< orphan*/  erif_list; int /*<<< orphan*/  counter_index; int /*<<< orphan*/  afa_block; int /*<<< orphan*/  priv; int /*<<< orphan*/  key; int /*<<< orphan*/  min_mtu; int /*<<< orphan*/  irif_index; int /*<<< orphan*/  action; } ;
struct mlxsw_sp_mr_tcam_ops {int (* route_create ) (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  route_priv_size; } ;
struct mlxsw_sp_mr_tcam {int /*<<< orphan*/  priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  route_action; int /*<<< orphan*/  min_mtu; int /*<<< orphan*/  irif_index; } ;
struct mlxsw_sp_mr_route_params {int /*<<< orphan*/  prio; TYPE_1__ value; int /*<<< orphan*/  key; } ;
struct mlxsw_sp {struct mlxsw_sp_mr_tcam_ops* mr_tcam_ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_flow_counter_alloc (struct mlxsw_sp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_flow_counter_free (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_mr_erif_list_flush (struct mlxsw_sp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_mr_erif_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_mr_tcam_afa_block_create (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_mr_tcam_afa_block_destroy (int /*<<< orphan*/ ) ; 
 int mlxsw_sp_mr_tcam_erif_populate (struct mlxsw_sp*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int stub1 (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mlxsw_sp_mr_tcam_route_create(struct mlxsw_sp *mlxsw_sp, void *priv,
			      void *route_priv,
			      struct mlxsw_sp_mr_route_params *route_params)
{
	const struct mlxsw_sp_mr_tcam_ops *ops = mlxsw_sp->mr_tcam_ops;
	struct mlxsw_sp_mr_tcam_route *route = route_priv;
	struct mlxsw_sp_mr_tcam *mr_tcam = priv;
	int err;

	route->key = route_params->key;
	route->irif_index = route_params->value.irif_index;
	route->min_mtu = route_params->value.min_mtu;
	route->action = route_params->value.route_action;

	/* Create the egress RIFs list */
	mlxsw_sp_mr_erif_list_init(&route->erif_list);
	err = mlxsw_sp_mr_tcam_erif_populate(mlxsw_sp, &route->erif_list,
					     &route_params->value);
	if (err)
		goto err_erif_populate;

	/* Create the flow counter */
	err = mlxsw_sp_flow_counter_alloc(mlxsw_sp, &route->counter_index);
	if (err)
		goto err_counter_alloc;

	/* Create the flexible action block */
	route->afa_block = mlxsw_sp_mr_tcam_afa_block_create(mlxsw_sp,
							     route->action,
							     route->irif_index,
							     route->counter_index,
							     route->min_mtu,
							     &route->erif_list);
	if (IS_ERR(route->afa_block)) {
		err = PTR_ERR(route->afa_block);
		goto err_afa_block_create;
	}

	route->priv = kzalloc(ops->route_priv_size, GFP_KERNEL);
	if (!route->priv) {
		err = -ENOMEM;
		goto err_route_priv_alloc;
	}

	/* Write the route to the TCAM */
	err = ops->route_create(mlxsw_sp, mr_tcam->priv, route->priv,
				&route->key, route->afa_block,
				route_params->prio);
	if (err)
		goto err_route_create;
	return 0;

err_route_create:
	kfree(route->priv);
err_route_priv_alloc:
	mlxsw_sp_mr_tcam_afa_block_destroy(route->afa_block);
err_afa_block_create:
	mlxsw_sp_flow_counter_free(mlxsw_sp, route->counter_index);
err_erif_populate:
err_counter_alloc:
	mlxsw_sp_mr_erif_list_flush(mlxsw_sp, &route->erif_list);
	return err;
}