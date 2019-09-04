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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_flow_table {int /*<<< orphan*/  node; } ;
struct mlx5_flow_steering {int /*<<< orphan*/  ftes_cache; } ;
struct mlx5_flow_act {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct fs_fte {TYPE_1__ node; struct mlx5_flow_act action; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct fs_fte* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FS_TYPE_FLOW_ENTRY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  del_hw_fte ; 
 int /*<<< orphan*/  del_sw_fte ; 
 struct mlx5_flow_steering* get_steering (int /*<<< orphan*/ *) ; 
 struct fs_fte* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tree_init_node (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fs_fte *alloc_fte(struct mlx5_flow_table *ft,
				u32 *match_value,
				struct mlx5_flow_act *flow_act)
{
	struct mlx5_flow_steering *steering = get_steering(&ft->node);
	struct fs_fte *fte;

	fte = kmem_cache_zalloc(steering->ftes_cache, GFP_KERNEL);
	if (!fte)
		return ERR_PTR(-ENOMEM);

	memcpy(fte->val, match_value, sizeof(fte->val));
	fte->node.type =  FS_TYPE_FLOW_ENTRY;
	fte->action = *flow_act;

	tree_init_node(&fte->node, del_hw_fte, del_sw_fte);

	return fte;
}