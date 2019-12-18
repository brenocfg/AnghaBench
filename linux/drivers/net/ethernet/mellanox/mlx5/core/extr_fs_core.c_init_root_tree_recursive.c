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
struct mlx5_flow_steering {int /*<<< orphan*/  dev; } ;
struct fs_node {int dummy; } ;
struct mlx5_flow_namespace {struct fs_node node; } ;
struct init_tree_node {scalar_t__ type; int min_ft_level; int ar_size; scalar_t__ num_leaf_prios; struct init_tree_node* children; int /*<<< orphan*/  def_miss_action; int /*<<< orphan*/  num_levels; int /*<<< orphan*/  caps; } ;
struct fs_prio {struct fs_node node; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_ft_level; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FS_TYPE_NAMESPACE ; 
 scalar_t__ FS_TYPE_PRIO ; 
 scalar_t__ IS_ERR (struct mlx5_flow_namespace*) ; 
 int MLX5_CAP_FLOWTABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct mlx5_flow_namespace*) ; 
 int create_leaf_prios (struct mlx5_flow_namespace*,int,struct init_tree_node*) ; 
 TYPE_1__ flow_table_properties_nic_receive ; 
 struct mlx5_flow_namespace* fs_create_namespace (struct mlx5_flow_namespace*,int /*<<< orphan*/ ) ; 
 struct mlx5_flow_namespace* fs_create_prio (struct mlx5_flow_namespace*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_get_obj (struct mlx5_flow_namespace*,struct fs_node*) ; 
 int /*<<< orphan*/  has_required_caps (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_root_tree_recursive(struct mlx5_flow_steering *steering,
				    struct init_tree_node *init_node,
				    struct fs_node *fs_parent_node,
				    struct init_tree_node *init_parent_node,
				    int prio)
{
	int max_ft_level = MLX5_CAP_FLOWTABLE(steering->dev,
					      flow_table_properties_nic_receive.
					      max_ft_level);
	struct mlx5_flow_namespace *fs_ns;
	struct fs_prio *fs_prio;
	struct fs_node *base;
	int i;
	int err;

	if (init_node->type == FS_TYPE_PRIO) {
		if ((init_node->min_ft_level > max_ft_level) ||
		    !has_required_caps(steering->dev, &init_node->caps))
			return 0;

		fs_get_obj(fs_ns, fs_parent_node);
		if (init_node->num_leaf_prios)
			return create_leaf_prios(fs_ns, prio, init_node);
		fs_prio = fs_create_prio(fs_ns, prio, init_node->num_levels);
		if (IS_ERR(fs_prio))
			return PTR_ERR(fs_prio);
		base = &fs_prio->node;
	} else if (init_node->type == FS_TYPE_NAMESPACE) {
		fs_get_obj(fs_prio, fs_parent_node);
		fs_ns = fs_create_namespace(fs_prio, init_node->def_miss_action);
		if (IS_ERR(fs_ns))
			return PTR_ERR(fs_ns);
		base = &fs_ns->node;
	} else {
		return -EINVAL;
	}
	prio = 0;
	for (i = 0; i < init_node->ar_size; i++) {
		err = init_root_tree_recursive(steering, &init_node->children[i],
					       base, init_node, prio);
		if (err)
			return err;
		if (init_node->children[i].type == FS_TYPE_PRIO &&
		    init_node->children[i].num_leaf_prios) {
			prio += init_node->children[i].num_leaf_prios;
		}
	}

	return 0;
}