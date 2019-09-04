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
typedef  int u8 ;
typedef  int u32 ;
struct mlx5e_flow_table {size_t num_groups; int /*<<< orphan*/ ** g; int /*<<< orphan*/  t; } ;
struct mlx5e_l2_table {struct mlx5e_flow_table ft; } ;
struct TYPE_2__ {int /*<<< orphan*/  dmac_47_16; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ MLX5E_L2_GROUP1_SIZE ; 
 scalar_t__ MLX5E_L2_GROUP2_SIZE ; 
 scalar_t__ MLX5E_L2_GROUP3_SIZE ; 
 int /*<<< orphan*/  MLX5E_NUM_L2_GROUPS ; 
 int* MLX5_ADDR_OF (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int MLX5_MATCH_OUTER_HEADERS ; 
 int /*<<< orphan*/  MLX5_SET_CFG (int*,int /*<<< orphan*/ ,int) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_flow_group_in ; 
 int /*<<< orphan*/  end_flow_index ; 
 int /*<<< orphan*/  eth_broadcast_addr (int*) ; 
 int /*<<< orphan*/  eth_zero_addr (int*) ; 
 int /*<<< orphan*/  fte_match_param ; 
 int /*<<< orphan*/ ** kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  kvfree (int*) ; 
 int* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  match_criteria ; 
 int /*<<< orphan*/  match_criteria_enable ; 
 void* mlx5_create_flow_group (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mlx5e_destroy_groups (struct mlx5e_flow_table*) ; 
 TYPE_1__ outer_headers ; 
 int /*<<< orphan*/  start_flow_index ; 

__attribute__((used)) static int mlx5e_create_l2_table_groups(struct mlx5e_l2_table *l2_table)
{
	int inlen = MLX5_ST_SZ_BYTES(create_flow_group_in);
	struct mlx5e_flow_table *ft = &l2_table->ft;
	int ix = 0;
	u8 *mc_dmac;
	u32 *in;
	int err;
	u8 *mc;

	ft->g = kcalloc(MLX5E_NUM_L2_GROUPS, sizeof(*ft->g), GFP_KERNEL);
	if (!ft->g)
		return -ENOMEM;
	in = kvzalloc(inlen, GFP_KERNEL);
	if (!in) {
		kfree(ft->g);
		return -ENOMEM;
	}

	mc = MLX5_ADDR_OF(create_flow_group_in, in, match_criteria);
	mc_dmac = MLX5_ADDR_OF(fte_match_param, mc,
			       outer_headers.dmac_47_16);
	/* Flow Group for promiscuous */
	MLX5_SET_CFG(in, start_flow_index, ix);
	ix += MLX5E_L2_GROUP1_SIZE;
	MLX5_SET_CFG(in, end_flow_index, ix - 1);
	ft->g[ft->num_groups] = mlx5_create_flow_group(ft->t, in);
	if (IS_ERR(ft->g[ft->num_groups]))
		goto err_destroy_groups;
	ft->num_groups++;

	/* Flow Group for full match */
	eth_broadcast_addr(mc_dmac);
	MLX5_SET_CFG(in, match_criteria_enable, MLX5_MATCH_OUTER_HEADERS);
	MLX5_SET_CFG(in, start_flow_index, ix);
	ix += MLX5E_L2_GROUP2_SIZE;
	MLX5_SET_CFG(in, end_flow_index, ix - 1);
	ft->g[ft->num_groups] = mlx5_create_flow_group(ft->t, in);
	if (IS_ERR(ft->g[ft->num_groups]))
		goto err_destroy_groups;
	ft->num_groups++;

	/* Flow Group for allmulti */
	eth_zero_addr(mc_dmac);
	mc_dmac[0] = 0x01;
	MLX5_SET_CFG(in, start_flow_index, ix);
	ix += MLX5E_L2_GROUP3_SIZE;
	MLX5_SET_CFG(in, end_flow_index, ix - 1);
	ft->g[ft->num_groups] = mlx5_create_flow_group(ft->t, in);
	if (IS_ERR(ft->g[ft->num_groups]))
		goto err_destroy_groups;
	ft->num_groups++;

	kvfree(in);
	return 0;

err_destroy_groups:
	err = PTR_ERR(ft->g[ft->num_groups]);
	ft->g[ft->num_groups] = NULL;
	mlx5e_destroy_groups(ft);
	kvfree(in);

	return err;
}