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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {struct mlx5_flow_table* acl; struct mlx5_flow_table* allow_untagged_spoofchk_grp; struct mlx5_flow_table* allow_untagged_only_grp; struct mlx5_flow_table* allow_spoofchk_only_grp; struct mlx5_flow_table* drop_grp; } ;
struct mlx5_vport {TYPE_1__ ingress; int /*<<< orphan*/  vport; } ;
struct mlx5_flow_table {int dummy; } ;
struct mlx5_flow_namespace {int dummy; } ;
typedef  struct mlx5_flow_table mlx5_flow_group ;
struct mlx5_eswitch {struct mlx5_core_dev* dev; } ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  smac_15_0; int /*<<< orphan*/  smac_47_16; int /*<<< orphan*/  cvlan_tag; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct mlx5_flow_table*) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct mlx5_flow_table*) ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  MLX5_CAP_ESW_INGRESS_ACL (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_FLOW_NAMESPACE_ESW_INGRESS ; 
 int MLX5_MATCH_OUTER_HEADERS ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MLX5_SET_TO_ONES (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct mlx5_flow_table*) ; 
 int /*<<< orphan*/  create_flow_group_in ; 
 int /*<<< orphan*/  end_flow_index ; 
 int /*<<< orphan*/  esw_debug (struct mlx5_core_dev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esw_warn (struct mlx5_core_dev*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ft_support ; 
 int /*<<< orphan*/  fte_match_param ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_max_ft_size ; 
 int /*<<< orphan*/  match_criteria_enable ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct mlx5_flow_table* mlx5_create_flow_group (struct mlx5_flow_table*,int /*<<< orphan*/ *) ; 
 struct mlx5_flow_table* mlx5_create_vport_flow_table (struct mlx5_flow_namespace*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_destroy_flow_group (struct mlx5_flow_table*) ; 
 int /*<<< orphan*/  mlx5_destroy_flow_table (struct mlx5_flow_table*) ; 
 int /*<<< orphan*/  mlx5_eswitch_vport_num_to_index (struct mlx5_eswitch*,int /*<<< orphan*/ ) ; 
 struct mlx5_flow_namespace* mlx5_get_flow_vport_acl_namespace (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ outer_headers ; 
 int /*<<< orphan*/  start_flow_index ; 

int esw_vport_enable_ingress_acl(struct mlx5_eswitch *esw,
				 struct mlx5_vport *vport)
{
	int inlen = MLX5_ST_SZ_BYTES(create_flow_group_in);
	struct mlx5_core_dev *dev = esw->dev;
	struct mlx5_flow_namespace *root_ns;
	struct mlx5_flow_table *acl;
	struct mlx5_flow_group *g;
	void *match_criteria;
	u32 *flow_group_in;
	/* The ingress acl table contains 4 groups
	 * (2 active rules at the same time -
	 *      1 allow rule from one of the first 3 groups.
	 *      1 drop rule from the last group):
	 * 1)Allow untagged traffic with smac=original mac.
	 * 2)Allow untagged traffic.
	 * 3)Allow traffic with smac=original mac.
	 * 4)Drop all other traffic.
	 */
	int table_size = 4;
	int err = 0;

	if (!MLX5_CAP_ESW_INGRESS_ACL(dev, ft_support))
		return -EOPNOTSUPP;

	if (!IS_ERR_OR_NULL(vport->ingress.acl))
		return 0;

	esw_debug(dev, "Create vport[%d] ingress ACL log_max_size(%d)\n",
		  vport->vport, MLX5_CAP_ESW_INGRESS_ACL(dev, log_max_ft_size));

	root_ns = mlx5_get_flow_vport_acl_namespace(dev, MLX5_FLOW_NAMESPACE_ESW_INGRESS,
			mlx5_eswitch_vport_num_to_index(esw, vport->vport));
	if (!root_ns) {
		esw_warn(dev, "Failed to get E-Switch ingress flow namespace for vport (%d)\n", vport->vport);
		return -EOPNOTSUPP;
	}

	flow_group_in = kvzalloc(inlen, GFP_KERNEL);
	if (!flow_group_in)
		return -ENOMEM;

	acl = mlx5_create_vport_flow_table(root_ns, 0, table_size, 0, vport->vport);
	if (IS_ERR(acl)) {
		err = PTR_ERR(acl);
		esw_warn(dev, "Failed to create E-Switch vport[%d] ingress flow Table, err(%d)\n",
			 vport->vport, err);
		goto out;
	}
	vport->ingress.acl = acl;

	match_criteria = MLX5_ADDR_OF(create_flow_group_in, flow_group_in, match_criteria);

	MLX5_SET(create_flow_group_in, flow_group_in, match_criteria_enable, MLX5_MATCH_OUTER_HEADERS);
	MLX5_SET_TO_ONES(fte_match_param, match_criteria, outer_headers.cvlan_tag);
	MLX5_SET_TO_ONES(fte_match_param, match_criteria, outer_headers.smac_47_16);
	MLX5_SET_TO_ONES(fte_match_param, match_criteria, outer_headers.smac_15_0);
	MLX5_SET(create_flow_group_in, flow_group_in, start_flow_index, 0);
	MLX5_SET(create_flow_group_in, flow_group_in, end_flow_index, 0);

	g = mlx5_create_flow_group(acl, flow_group_in);
	if (IS_ERR(g)) {
		err = PTR_ERR(g);
		esw_warn(dev, "Failed to create E-Switch vport[%d] ingress untagged spoofchk flow group, err(%d)\n",
			 vport->vport, err);
		goto out;
	}
	vport->ingress.allow_untagged_spoofchk_grp = g;

	memset(flow_group_in, 0, inlen);
	MLX5_SET(create_flow_group_in, flow_group_in, match_criteria_enable, MLX5_MATCH_OUTER_HEADERS);
	MLX5_SET_TO_ONES(fte_match_param, match_criteria, outer_headers.cvlan_tag);
	MLX5_SET(create_flow_group_in, flow_group_in, start_flow_index, 1);
	MLX5_SET(create_flow_group_in, flow_group_in, end_flow_index, 1);

	g = mlx5_create_flow_group(acl, flow_group_in);
	if (IS_ERR(g)) {
		err = PTR_ERR(g);
		esw_warn(dev, "Failed to create E-Switch vport[%d] ingress untagged flow group, err(%d)\n",
			 vport->vport, err);
		goto out;
	}
	vport->ingress.allow_untagged_only_grp = g;

	memset(flow_group_in, 0, inlen);
	MLX5_SET(create_flow_group_in, flow_group_in, match_criteria_enable, MLX5_MATCH_OUTER_HEADERS);
	MLX5_SET_TO_ONES(fte_match_param, match_criteria, outer_headers.smac_47_16);
	MLX5_SET_TO_ONES(fte_match_param, match_criteria, outer_headers.smac_15_0);
	MLX5_SET(create_flow_group_in, flow_group_in, start_flow_index, 2);
	MLX5_SET(create_flow_group_in, flow_group_in, end_flow_index, 2);

	g = mlx5_create_flow_group(acl, flow_group_in);
	if (IS_ERR(g)) {
		err = PTR_ERR(g);
		esw_warn(dev, "Failed to create E-Switch vport[%d] ingress spoofchk flow group, err(%d)\n",
			 vport->vport, err);
		goto out;
	}
	vport->ingress.allow_spoofchk_only_grp = g;

	memset(flow_group_in, 0, inlen);
	MLX5_SET(create_flow_group_in, flow_group_in, start_flow_index, 3);
	MLX5_SET(create_flow_group_in, flow_group_in, end_flow_index, 3);

	g = mlx5_create_flow_group(acl, flow_group_in);
	if (IS_ERR(g)) {
		err = PTR_ERR(g);
		esw_warn(dev, "Failed to create E-Switch vport[%d] ingress drop flow group, err(%d)\n",
			 vport->vport, err);
		goto out;
	}
	vport->ingress.drop_grp = g;

out:
	if (err) {
		if (!IS_ERR_OR_NULL(vport->ingress.allow_spoofchk_only_grp))
			mlx5_destroy_flow_group(
					vport->ingress.allow_spoofchk_only_grp);
		if (!IS_ERR_OR_NULL(vport->ingress.allow_untagged_only_grp))
			mlx5_destroy_flow_group(
					vport->ingress.allow_untagged_only_grp);
		if (!IS_ERR_OR_NULL(vport->ingress.allow_untagged_spoofchk_grp))
			mlx5_destroy_flow_group(
				vport->ingress.allow_untagged_spoofchk_grp);
		if (!IS_ERR_OR_NULL(vport->ingress.acl))
			mlx5_destroy_flow_table(vport->ingress.acl);
	}

	kvfree(flow_group_in);
	return err;
}