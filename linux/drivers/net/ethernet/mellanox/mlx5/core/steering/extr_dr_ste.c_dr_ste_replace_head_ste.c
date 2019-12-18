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
struct mlx5dr_ste_send_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_of_valid_entries; int /*<<< orphan*/  num_of_collisions; } ;
struct mlx5dr_ste_htbl {TYPE_1__ ctrl; } ;
struct mlx5dr_ste {int /*<<< orphan*/  hw_ste; int /*<<< orphan*/  miss_list_node; struct mlx5dr_ste_htbl* htbl; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DR_STE_SIZE_REDUCED ; 
 int /*<<< orphan*/  dr_ste_replace (struct mlx5dr_ste*,struct mlx5dr_ste*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5dr_htbl_put (struct mlx5dr_ste_htbl*) ; 
 int /*<<< orphan*/  mlx5dr_rule_update_rule_member (struct mlx5dr_ste*,struct mlx5dr_ste*) ; 
 int /*<<< orphan*/  mlx5dr_send_fill_and_append_ste_send_info (struct mlx5dr_ste*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlx5dr_ste_send_info*,struct list_head*,int) ; 

__attribute__((used)) static void
dr_ste_replace_head_ste(struct mlx5dr_ste *ste, struct mlx5dr_ste *next_ste,
			struct mlx5dr_ste_send_info *ste_info_head,
			struct list_head *send_ste_list,
			struct mlx5dr_ste_htbl *stats_tbl)

{
	struct mlx5dr_ste_htbl *next_miss_htbl;

	next_miss_htbl = next_ste->htbl;

	/* Remove from the miss_list the next_ste before copy */
	list_del_init(&next_ste->miss_list_node);

	/* All rule-members that use next_ste should know about that */
	mlx5dr_rule_update_rule_member(next_ste, ste);

	/* Move data from next into ste */
	dr_ste_replace(ste, next_ste);

	/* Del the htbl that contains the next_ste.
	 * The origin htbl stay with the same number of entries.
	 */
	mlx5dr_htbl_put(next_miss_htbl);

	mlx5dr_send_fill_and_append_ste_send_info(ste, DR_STE_SIZE_REDUCED,
						  0, ste->hw_ste,
						  ste_info_head,
						  send_ste_list,
						  true /* Copy data */);

	stats_tbl->ctrl.num_of_collisions--;
	stats_tbl->ctrl.num_of_valid_entries--;
}