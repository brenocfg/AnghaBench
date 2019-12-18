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
typedef  int /*<<< orphan*/  u8 ;
struct mlx5_flow_steering {int /*<<< orphan*/  fgs_cache; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int /*<<< orphan*/  match_criteria; int /*<<< orphan*/  match_criteria_enable; } ;
struct mlx5_flow_group {int start_index; int max_ftes; TYPE_2__ node; TYPE_1__ mask; int /*<<< orphan*/  fte_allocator; int /*<<< orphan*/  ftes_hash; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct mlx5_flow_group* ERR_PTR (int) ; 
 int /*<<< orphan*/  FS_TYPE_FLOW_GROUP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ida_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct mlx5_flow_group*) ; 
 struct mlx5_flow_group* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,int) ; 
 int /*<<< orphan*/  rhash_fte ; 
 int rhashtable_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mlx5_flow_group *alloc_flow_group(struct mlx5_flow_steering *steering,
						u8 match_criteria_enable,
						const void *match_criteria,
						int start_index,
						int end_index)
{
	struct mlx5_flow_group *fg;
	int ret;

	fg = kmem_cache_zalloc(steering->fgs_cache, GFP_KERNEL);
	if (!fg)
		return ERR_PTR(-ENOMEM);

	ret = rhashtable_init(&fg->ftes_hash, &rhash_fte);
	if (ret) {
		kmem_cache_free(steering->fgs_cache, fg);
		return ERR_PTR(ret);
	}

	ida_init(&fg->fte_allocator);
	fg->mask.match_criteria_enable = match_criteria_enable;
	memcpy(&fg->mask.match_criteria, match_criteria,
	       sizeof(fg->mask.match_criteria));
	fg->node.type =  FS_TYPE_FLOW_GROUP;
	fg->start_index = start_index;
	fg->max_ftes = end_index - start_index + 1;

	return fg;
}