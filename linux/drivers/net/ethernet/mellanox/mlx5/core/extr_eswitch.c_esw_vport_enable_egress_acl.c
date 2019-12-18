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
struct TYPE_3__ {struct mlx5_flow_table* allowed_vlans_grp; struct mlx5_flow_table* drop_grp; struct mlx5_flow_table* acl; } ;
struct mlx5_vport {TYPE_1__ egress; int /*<<< orphan*/  vport; } ;
struct mlx5_flow_table {int dummy; } ;
struct mlx5_flow_namespace {int dummy; } ;
typedef  struct mlx5_flow_table mlx5_flow_group ;
struct mlx5_eswitch {struct mlx5_core_dev* dev; } ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  first_vid; int /*<<< orphan*/  cvlan_tag; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct mlx5_flow_table*) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct mlx5_flow_table*) ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  MLX5_CAP_ESW_EGRESS_ACL (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_FLOW_NAMESPACE_ESW_EGRESS ; 
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

int esw_vport_enable_egress_acl(struct mlx5_eswitch *esw,
				struct mlx5_vport *vport)
{
	int inlen = MLX5_ST_SZ_BYTES(create_flow_group_in);
	struct mlx5_flow_group *vlan_grp = NULL;
	struct mlx5_flow_group *drop_grp = NULL;
	struct mlx5_core_dev *dev = esw->dev;
	struct mlx5_flow_namespace *root_ns;
	struct mlx5_flow_table *acl;
	void *match_criteria;
	u32 *flow_group_in;
	/* The egress acl table contains 2 rules:
	 * 1)Allow traffic with vlan_tag=vst_vlan_id
	 * 2)Drop all other traffic.
	 */
	int table_size = 2;
	int err = 0;

	if (!MLX5_CAP_ESW_EGRESS_ACL(dev, ft_support))
		return -EOPNOTSUPP;

	if (!IS_ERR_OR_NULL(vport->egress.acl))
		return 0;

	esw_debug(dev, "Create vport[%d] egress ACL log_max_size(%d)\n",
		  vport->vport, MLX5_CAP_ESW_EGRESS_ACL(dev, log_max_ft_size));

	root_ns = mlx5_get_flow_vport_acl_namespace(dev, MLX5_FLOW_NAMESPACE_ESW_EGRESS,
			mlx5_eswitch_vport_num_to_index(esw, vport->vport));
	if (!root_ns) {
		esw_warn(dev, "Failed to get E-Switch egress flow namespace for vport (%d)\n", vport->vport);
		return -EOPNOTSUPP;
	}

	flow_group_in = kvzalloc(inlen, GFP_KERNEL);
	if (!flow_group_in)
		return -ENOMEM;

	acl = mlx5_create_vport_flow_table(root_ns, 0, table_size, 0, vport->vport);
	if (IS_ERR(acl)) {
		err = PTR_ERR(acl);
		esw_warn(dev, "Failed to create E-Switch vport[%d] egress flow Table, err(%d)\n",
			 vport->vport, err);
		goto out;
	}

	MLX5_SET(create_flow_group_in, flow_group_in, match_criteria_enable, MLX5_MATCH_OUTER_HEADERS);
	match_criteria = MLX5_ADDR_OF(create_flow_group_in, flow_group_in, match_criteria);
	MLX5_SET_TO_ONES(fte_match_param, match_criteria, outer_headers.cvlan_tag);
	MLX5_SET_TO_ONES(fte_match_param, match_criteria, outer_headers.first_vid);
	MLX5_SET(create_flow_group_in, flow_group_in, start_flow_index, 0);
	MLX5_SET(create_flow_group_in, flow_group_in, end_flow_index, 0);

	vlan_grp = mlx5_create_flow_group(acl, flow_group_in);
	if (IS_ERR(vlan_grp)) {
		err = PTR_ERR(vlan_grp);
		esw_warn(dev, "Failed to create E-Switch vport[%d] egress allowed vlans flow group, err(%d)\n",
			 vport->vport, err);
		goto out;
	}

	memset(flow_group_in, 0, inlen);
	MLX5_SET(create_flow_group_in, flow_group_in, start_flow_index, 1);
	MLX5_SET(create_flow_group_in, flow_group_in, end_flow_index, 1);
	drop_grp = mlx5_create_flow_group(acl, flow_group_in);
	if (IS_ERR(drop_grp)) {
		err = PTR_ERR(drop_grp);
		esw_warn(dev, "Failed to create E-Switch vport[%d] egress drop flow group, err(%d)\n",
			 vport->vport, err);
		goto out;
	}

	vport->egress.acl = acl;
	vport->egress.drop_grp = drop_grp;
	vport->egress.allowed_vlans_grp = vlan_grp;
out:
	kvfree(flow_group_in);
	if (err && !IS_ERR_OR_NULL(vlan_grp))
		mlx5_destroy_flow_group(vlan_grp);
	if (err && !IS_ERR_OR_NULL(acl))
		mlx5_destroy_flow_table(acl);
	return err;
}