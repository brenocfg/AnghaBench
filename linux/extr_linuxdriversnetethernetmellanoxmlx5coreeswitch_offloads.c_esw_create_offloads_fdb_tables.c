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
typedef  int u8 ;
typedef  void u32 ;
struct mlx5_flow_table_attr {int max_fte; int /*<<< orphan*/  prio; } ;
struct mlx5_flow_table {int dummy; } ;
struct mlx5_flow_namespace {int dummy; } ;
typedef  struct mlx5_flow_table mlx5_flow_group ;
struct TYPE_5__ {struct mlx5_flow_table* slow_fdb; struct mlx5_flow_table* send_to_vport_grp; struct mlx5_flow_table* miss_grp; } ;
struct TYPE_6__ {TYPE_1__ offloads; } ;
struct mlx5_eswitch {TYPE_2__ fdb_table; struct mlx5_core_dev* dev; } ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  source_port; int /*<<< orphan*/  source_sqn; } ;
struct TYPE_7__ {void* dmac_47_16; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FDB_SLOW_PATH ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct mlx5_flow_table*) ; 
 int MAX_PF_SQ ; 
 int MAX_SQ_NVPORTS ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  MLX5_FLOW_NAMESPACE_FDB ; 
 int MLX5_MATCH_MISC_PARAMETERS ; 
 int MLX5_MATCH_OUTER_HEADERS ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MLX5_SET_TO_ONES (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct mlx5_flow_table*) ; 
 int /*<<< orphan*/  create_flow_group_in ; 
 int /*<<< orphan*/  end_flow_index ; 
 int esw_add_fdb_miss_rule (struct mlx5_eswitch*) ; 
 int esw_create_offloads_fast_fdb_table (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  esw_debug (struct mlx5_core_dev*,char*) ; 
 int /*<<< orphan*/  esw_destroy_offloads_fast_fdb_table (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  esw_warn (struct mlx5_core_dev*,char*,...) ; 
 int /*<<< orphan*/  fte_match_param ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 void* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  match_criteria_enable ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 TYPE_4__ misc_parameters ; 
 struct mlx5_flow_table* mlx5_create_flow_group (struct mlx5_flow_table*,void*) ; 
 struct mlx5_flow_table* mlx5_create_flow_table (struct mlx5_flow_namespace*,struct mlx5_flow_table_attr*) ; 
 int /*<<< orphan*/  mlx5_destroy_flow_group (struct mlx5_flow_table*) ; 
 int /*<<< orphan*/  mlx5_destroy_flow_table (struct mlx5_flow_table*) ; 
 struct mlx5_flow_namespace* mlx5_get_flow_namespace (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 TYPE_3__ outer_headers ; 
 int /*<<< orphan*/  start_flow_index ; 

__attribute__((used)) static int esw_create_offloads_fdb_tables(struct mlx5_eswitch *esw, int nvports)
{
	int inlen = MLX5_ST_SZ_BYTES(create_flow_group_in);
	struct mlx5_flow_table_attr ft_attr = {};
	struct mlx5_core_dev *dev = esw->dev;
	struct mlx5_flow_namespace *root_ns;
	struct mlx5_flow_table *fdb = NULL;
	int table_size, ix, err = 0;
	struct mlx5_flow_group *g;
	void *match_criteria;
	u32 *flow_group_in;
	u8 *dmac;

	esw_debug(esw->dev, "Create offloads FDB Tables\n");
	flow_group_in = kvzalloc(inlen, GFP_KERNEL);
	if (!flow_group_in)
		return -ENOMEM;

	root_ns = mlx5_get_flow_namespace(dev, MLX5_FLOW_NAMESPACE_FDB);
	if (!root_ns) {
		esw_warn(dev, "Failed to get FDB flow namespace\n");
		err = -EOPNOTSUPP;
		goto ns_err;
	}

	err = esw_create_offloads_fast_fdb_table(esw);
	if (err)
		goto fast_fdb_err;

	table_size = nvports * MAX_SQ_NVPORTS + MAX_PF_SQ + 2;

	ft_attr.max_fte = table_size;
	ft_attr.prio = FDB_SLOW_PATH;

	fdb = mlx5_create_flow_table(root_ns, &ft_attr);
	if (IS_ERR(fdb)) {
		err = PTR_ERR(fdb);
		esw_warn(dev, "Failed to create slow path FDB Table err %d\n", err);
		goto slow_fdb_err;
	}
	esw->fdb_table.offloads.slow_fdb = fdb;

	/* create send-to-vport group */
	memset(flow_group_in, 0, inlen);
	MLX5_SET(create_flow_group_in, flow_group_in, match_criteria_enable,
		 MLX5_MATCH_MISC_PARAMETERS);

	match_criteria = MLX5_ADDR_OF(create_flow_group_in, flow_group_in, match_criteria);

	MLX5_SET_TO_ONES(fte_match_param, match_criteria, misc_parameters.source_sqn);
	MLX5_SET_TO_ONES(fte_match_param, match_criteria, misc_parameters.source_port);

	ix = nvports * MAX_SQ_NVPORTS + MAX_PF_SQ;
	MLX5_SET(create_flow_group_in, flow_group_in, start_flow_index, 0);
	MLX5_SET(create_flow_group_in, flow_group_in, end_flow_index, ix - 1);

	g = mlx5_create_flow_group(fdb, flow_group_in);
	if (IS_ERR(g)) {
		err = PTR_ERR(g);
		esw_warn(dev, "Failed to create send-to-vport flow group err(%d)\n", err);
		goto send_vport_err;
	}
	esw->fdb_table.offloads.send_to_vport_grp = g;

	/* create miss group */
	memset(flow_group_in, 0, inlen);
	MLX5_SET(create_flow_group_in, flow_group_in, match_criteria_enable,
		 MLX5_MATCH_OUTER_HEADERS);
	match_criteria = MLX5_ADDR_OF(create_flow_group_in, flow_group_in,
				      match_criteria);
	dmac = MLX5_ADDR_OF(fte_match_param, match_criteria,
			    outer_headers.dmac_47_16);
	dmac[0] = 0x01;

	MLX5_SET(create_flow_group_in, flow_group_in, start_flow_index, ix);
	MLX5_SET(create_flow_group_in, flow_group_in, end_flow_index, ix + 2);

	g = mlx5_create_flow_group(fdb, flow_group_in);
	if (IS_ERR(g)) {
		err = PTR_ERR(g);
		esw_warn(dev, "Failed to create miss flow group err(%d)\n", err);
		goto miss_err;
	}
	esw->fdb_table.offloads.miss_grp = g;

	err = esw_add_fdb_miss_rule(esw);
	if (err)
		goto miss_rule_err;

	kvfree(flow_group_in);
	return 0;

miss_rule_err:
	mlx5_destroy_flow_group(esw->fdb_table.offloads.miss_grp);
miss_err:
	mlx5_destroy_flow_group(esw->fdb_table.offloads.send_to_vport_grp);
send_vport_err:
	mlx5_destroy_flow_table(esw->fdb_table.offloads.slow_fdb);
slow_fdb_err:
	esw_destroy_offloads_fast_fdb_table(esw);
fast_fdb_err:
ns_err:
	kvfree(flow_group_in);
	return err;
}