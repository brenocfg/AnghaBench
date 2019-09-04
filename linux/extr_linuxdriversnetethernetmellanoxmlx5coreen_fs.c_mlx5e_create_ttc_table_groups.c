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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mlx5e_flow_table {size_t num_groups; int /*<<< orphan*/ ** g; int /*<<< orphan*/  t; } ;
struct mlx5e_ttc_table {struct mlx5e_flow_table ft; } ;
struct TYPE_2__ {int /*<<< orphan*/  ip_protocol; int /*<<< orphan*/  ethertype; int /*<<< orphan*/  ip_version; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ MLX5E_TTC_GROUP1_SIZE ; 
 scalar_t__ MLX5E_TTC_GROUP2_SIZE ; 
 scalar_t__ MLX5E_TTC_GROUP3_SIZE ; 
 int /*<<< orphan*/  MLX5E_TTC_NUM_GROUPS ; 
 int /*<<< orphan*/ * MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MLX5_MATCH_OUTER_HEADERS ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET_CFG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MLX5_SET_TO_ONES (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_flow_group_in ; 
 int /*<<< orphan*/  end_flow_index ; 
 int /*<<< orphan*/  fte_match_param ; 
 int /*<<< orphan*/ ** kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  match_criteria ; 
 int /*<<< orphan*/  match_criteria_enable ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* mlx5_create_flow_group (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ outer_headers ; 
 int /*<<< orphan*/  start_flow_index ; 

__attribute__((used)) static int mlx5e_create_ttc_table_groups(struct mlx5e_ttc_table *ttc,
					 bool use_ipv)
{
	int inlen = MLX5_ST_SZ_BYTES(create_flow_group_in);
	struct mlx5e_flow_table *ft = &ttc->ft;
	int ix = 0;
	u32 *in;
	int err;
	u8 *mc;

	ft->g = kcalloc(MLX5E_TTC_NUM_GROUPS,
			sizeof(*ft->g), GFP_KERNEL);
	if (!ft->g)
		return -ENOMEM;
	in = kvzalloc(inlen, GFP_KERNEL);
	if (!in) {
		kfree(ft->g);
		return -ENOMEM;
	}

	/* L4 Group */
	mc = MLX5_ADDR_OF(create_flow_group_in, in, match_criteria);
	MLX5_SET_TO_ONES(fte_match_param, mc, outer_headers.ip_protocol);
	if (use_ipv)
		MLX5_SET_TO_ONES(fte_match_param, mc, outer_headers.ip_version);
	else
		MLX5_SET_TO_ONES(fte_match_param, mc, outer_headers.ethertype);
	MLX5_SET_CFG(in, match_criteria_enable, MLX5_MATCH_OUTER_HEADERS);
	MLX5_SET_CFG(in, start_flow_index, ix);
	ix += MLX5E_TTC_GROUP1_SIZE;
	MLX5_SET_CFG(in, end_flow_index, ix - 1);
	ft->g[ft->num_groups] = mlx5_create_flow_group(ft->t, in);
	if (IS_ERR(ft->g[ft->num_groups]))
		goto err;
	ft->num_groups++;

	/* L3 Group */
	MLX5_SET(fte_match_param, mc, outer_headers.ip_protocol, 0);
	MLX5_SET_CFG(in, start_flow_index, ix);
	ix += MLX5E_TTC_GROUP2_SIZE;
	MLX5_SET_CFG(in, end_flow_index, ix - 1);
	ft->g[ft->num_groups] = mlx5_create_flow_group(ft->t, in);
	if (IS_ERR(ft->g[ft->num_groups]))
		goto err;
	ft->num_groups++;

	/* Any Group */
	memset(in, 0, inlen);
	MLX5_SET_CFG(in, start_flow_index, ix);
	ix += MLX5E_TTC_GROUP3_SIZE;
	MLX5_SET_CFG(in, end_flow_index, ix - 1);
	ft->g[ft->num_groups] = mlx5_create_flow_group(ft->t, in);
	if (IS_ERR(ft->g[ft->num_groups]))
		goto err;
	ft->num_groups++;

	kvfree(in);
	return 0;

err:
	err = PTR_ERR(ft->g[ft->num_groups]);
	ft->g[ft->num_groups] = NULL;
	kvfree(in);

	return err;
}