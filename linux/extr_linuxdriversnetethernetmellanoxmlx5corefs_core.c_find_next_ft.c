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
struct TYPE_4__ {int /*<<< orphan*/  list; int /*<<< orphan*/  parent; } ;
struct mlx5_flow_table {TYPE_1__ node; } ;
struct TYPE_5__ {int /*<<< orphan*/  children; } ;
struct fs_prio {TYPE_2__ node; } ;
struct TYPE_6__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 struct mlx5_flow_table* find_next_chained_ft (struct fs_prio*) ; 
 int /*<<< orphan*/  fs_get_obj (struct fs_prio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_is_last (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mlx5_flow_table* list_next_entry (struct mlx5_flow_table*,int /*<<< orphan*/ ) ; 
 TYPE_3__ node ; 

__attribute__((used)) static struct mlx5_flow_table *find_next_ft(struct mlx5_flow_table *ft)
{
	struct fs_prio *prio;

	fs_get_obj(prio, ft->node.parent);

	if (!list_is_last(&ft->node.list, &prio->node.children))
		return list_next_entry(ft, node.list);
	return find_next_chained_ft(prio);
}