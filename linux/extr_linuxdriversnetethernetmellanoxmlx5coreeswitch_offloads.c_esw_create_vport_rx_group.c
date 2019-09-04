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
typedef  void u32 ;
struct TYPE_4__ {int num_vfs; } ;
struct mlx5_priv {TYPE_1__ sriov; } ;
struct mlx5_flow_group {int dummy; } ;
struct TYPE_5__ {struct mlx5_flow_group* vport_rx_group; int /*<<< orphan*/  ft_offloads; } ;
struct mlx5_eswitch {TYPE_2__ offloads; TYPE_3__* dev; } ;
struct TYPE_6__ {struct mlx5_priv priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct mlx5_flow_group*) ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,void*,void*) ; 
 int MLX5_MATCH_MISC_PARAMETERS ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MLX5_SET_TO_ONES (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct mlx5_flow_group*) ; 
 int /*<<< orphan*/  create_flow_group_in ; 
 int /*<<< orphan*/  end_flow_index ; 
 int /*<<< orphan*/  fte_match_param ; 
 int /*<<< orphan*/  fte_match_set_misc ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 void* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  match_criteria_enable ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 void* misc_parameters ; 
 int /*<<< orphan*/  mlx5_core_warn (TYPE_3__*,char*,int) ; 
 struct mlx5_flow_group* mlx5_create_flow_group (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  source_port ; 
 int /*<<< orphan*/  start_flow_index ; 

__attribute__((used)) static int esw_create_vport_rx_group(struct mlx5_eswitch *esw)
{
	int inlen = MLX5_ST_SZ_BYTES(create_flow_group_in);
	struct mlx5_flow_group *g;
	struct mlx5_priv *priv = &esw->dev->priv;
	u32 *flow_group_in;
	void *match_criteria, *misc;
	int err = 0;
	int nvports = priv->sriov.num_vfs + 2;

	flow_group_in = kvzalloc(inlen, GFP_KERNEL);
	if (!flow_group_in)
		return -ENOMEM;

	/* create vport rx group */
	memset(flow_group_in, 0, inlen);
	MLX5_SET(create_flow_group_in, flow_group_in, match_criteria_enable,
		 MLX5_MATCH_MISC_PARAMETERS);

	match_criteria = MLX5_ADDR_OF(create_flow_group_in, flow_group_in, match_criteria);
	misc = MLX5_ADDR_OF(fte_match_param, match_criteria, misc_parameters);
	MLX5_SET_TO_ONES(fte_match_set_misc, misc, source_port);

	MLX5_SET(create_flow_group_in, flow_group_in, start_flow_index, 0);
	MLX5_SET(create_flow_group_in, flow_group_in, end_flow_index, nvports - 1);

	g = mlx5_create_flow_group(esw->offloads.ft_offloads, flow_group_in);

	if (IS_ERR(g)) {
		err = PTR_ERR(g);
		mlx5_core_warn(esw->dev, "Failed to create vport rx group err %d\n", err);
		goto out;
	}

	esw->offloads.vport_rx_group = g;
out:
	kvfree(flow_group_in);
	return err;
}