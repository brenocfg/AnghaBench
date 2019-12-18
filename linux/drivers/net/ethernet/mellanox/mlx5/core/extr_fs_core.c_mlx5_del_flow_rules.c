#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct mlx5_flow_handle {int num_rules; TYPE_1__** rule; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct fs_fte {TYPE_2__ node; scalar_t__ dests_size; scalar_t__ modify_mask; } ;
struct TYPE_9__ {int /*<<< orphan*/  parent; } ;
struct TYPE_7__ {TYPE_3__ node; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_hw_fte (TYPE_2__*) ; 
 int /*<<< orphan*/  down_write_ref_node (TYPE_2__*,int) ; 
 int /*<<< orphan*/  fs_get_obj (struct fs_fte*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx5_flow_handle*) ; 
 int /*<<< orphan*/  modify_fte (struct fs_fte*) ; 
 int /*<<< orphan*/  tree_put_node (TYPE_2__*,int) ; 
 int /*<<< orphan*/  tree_remove_node (TYPE_3__*,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write_ref_node (TYPE_2__*,int) ; 

void mlx5_del_flow_rules(struct mlx5_flow_handle *handle)
{
	struct fs_fte *fte;
	int i;

	/* In order to consolidate the HW changes we lock the FTE for other
	 * changes, and increase its refcount, in order not to perform the
	 * "del" functions of the FTE. Will handle them here.
	 * The removal of the rules is done under locked FTE.
	 * After removing all the handle's rules, if there are remaining
	 * rules, it means we just need to modify the FTE in FW, and
	 * unlock/decrease the refcount we increased before.
	 * Otherwise, it means the FTE should be deleted. First delete the
	 * FTE in FW. Then, unlock the FTE, and proceed the tree_put_node of
	 * the FTE, which will handle the last decrease of the refcount, as
	 * well as required handling of its parent.
	 */
	fs_get_obj(fte, handle->rule[0]->node.parent);
	down_write_ref_node(&fte->node, false);
	for (i = handle->num_rules - 1; i >= 0; i--)
		tree_remove_node(&handle->rule[i]->node, true);
	if (fte->modify_mask && fte->dests_size) {
		modify_fte(fte);
		up_write_ref_node(&fte->node, false);
	} else {
		del_hw_fte(&fte->node);
		up_write(&fte->node.lock);
		tree_put_node(&fte->node, false);
	}
	kfree(handle);
}