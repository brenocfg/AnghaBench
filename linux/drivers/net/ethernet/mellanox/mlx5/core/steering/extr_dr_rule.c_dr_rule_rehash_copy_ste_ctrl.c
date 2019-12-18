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
struct mlx5dr_ste {int /*<<< orphan*/  rule_list; int /*<<< orphan*/  refcount; TYPE_1__* next_htbl; int /*<<< orphan*/  ste_chain_location; } ;
struct mlx5dr_matcher_rx_tx {int dummy; } ;
struct mlx5dr_matcher {int dummy; } ;
struct TYPE_2__ {struct mlx5dr_ste* pointing_ste; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_tail_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5dr_rule_update_rule_member (struct mlx5dr_ste*,struct mlx5dr_ste*) ; 
 int /*<<< orphan*/  mlx5dr_ste_is_last_in_rule (struct mlx5dr_matcher_rx_tx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dr_rule_rehash_copy_ste_ctrl(struct mlx5dr_matcher *matcher,
					 struct mlx5dr_matcher_rx_tx *nic_matcher,
					 struct mlx5dr_ste *cur_ste,
					 struct mlx5dr_ste *new_ste)
{
	new_ste->next_htbl = cur_ste->next_htbl;
	new_ste->ste_chain_location = cur_ste->ste_chain_location;

	if (!mlx5dr_ste_is_last_in_rule(nic_matcher, new_ste->ste_chain_location))
		new_ste->next_htbl->pointing_ste = new_ste;

	/* We need to copy the refcount since this ste
	 * may have been traversed several times
	 */
	refcount_set(&new_ste->refcount, refcount_read(&cur_ste->refcount));

	/* Link old STEs rule_mem list to the new ste */
	mlx5dr_rule_update_rule_member(cur_ste, new_ste);
	INIT_LIST_HEAD(&new_ste->rule_list);
	list_splice_tail_init(&cur_ste->rule_list, &new_ste->rule_list);
}