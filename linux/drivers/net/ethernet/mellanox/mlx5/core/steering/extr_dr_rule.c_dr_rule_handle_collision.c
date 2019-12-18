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
typedef  int /*<<< orphan*/  u8 ;
struct mlx5dr_ste_send_info {int dummy; } ;
struct mlx5dr_ste {TYPE_3__* htbl; } ;
struct mlx5dr_matcher_rx_tx {int dummy; } ;
struct mlx5dr_matcher {TYPE_1__* tbl; } ;
struct list_head {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  num_of_valid_entries; int /*<<< orphan*/  num_of_collisions; } ;
struct TYPE_6__ {TYPE_2__ ctrl; } ;
struct TYPE_4__ {int /*<<< orphan*/  dmn; } ;

/* Variables and functions */
 int /*<<< orphan*/  DR_STE_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ dr_rule_append_to_miss_list (struct mlx5dr_ste*,struct list_head*,struct list_head*) ; 
 struct mlx5dr_ste* dr_rule_create_collision_entry (struct mlx5dr_matcher*,struct mlx5dr_matcher_rx_tx*,int /*<<< orphan*/ *,struct mlx5dr_ste*) ; 
 int /*<<< orphan*/  kfree (struct mlx5dr_ste_send_info*) ; 
 struct mlx5dr_ste_send_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5dr_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlx5dr_send_fill_and_append_ste_send_info (struct mlx5dr_ste*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mlx5dr_ste_send_info*,struct list_head*,int) ; 
 int /*<<< orphan*/  mlx5dr_ste_free (struct mlx5dr_ste*,struct mlx5dr_matcher*,struct mlx5dr_matcher_rx_tx*) ; 

__attribute__((used)) static struct mlx5dr_ste *
dr_rule_handle_collision(struct mlx5dr_matcher *matcher,
			 struct mlx5dr_matcher_rx_tx *nic_matcher,
			 struct mlx5dr_ste *ste,
			 u8 *hw_ste,
			 struct list_head *miss_list,
			 struct list_head *send_list)
{
	struct mlx5dr_ste_send_info *ste_info;
	struct mlx5dr_ste *new_ste;

	ste_info = kzalloc(sizeof(*ste_info), GFP_KERNEL);
	if (!ste_info)
		return NULL;

	new_ste = dr_rule_create_collision_entry(matcher, nic_matcher, hw_ste, ste);
	if (!new_ste)
		goto free_send_info;

	if (dr_rule_append_to_miss_list(new_ste, miss_list, send_list)) {
		mlx5dr_dbg(matcher->tbl->dmn, "Failed to update prev miss_list\n");
		goto err_exit;
	}

	mlx5dr_send_fill_and_append_ste_send_info(new_ste, DR_STE_SIZE, 0, hw_ste,
						  ste_info, send_list, false);

	ste->htbl->ctrl.num_of_collisions++;
	ste->htbl->ctrl.num_of_valid_entries++;

	return new_ste;

err_exit:
	mlx5dr_ste_free(new_ste, matcher, nic_matcher);
free_send_info:
	kfree(ste_info);
	return NULL;
}