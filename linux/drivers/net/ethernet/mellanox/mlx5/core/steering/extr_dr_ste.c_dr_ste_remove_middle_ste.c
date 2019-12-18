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
typedef  int /*<<< orphan*/  u64 ;
struct mlx5dr_ste_send_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_of_collisions; int /*<<< orphan*/  num_of_valid_entries; } ;
struct mlx5dr_ste_htbl {TYPE_1__ ctrl; } ;
struct mlx5dr_ste {int /*<<< orphan*/  miss_list_node; int /*<<< orphan*/  hw_ste; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DR_STE_SIZE_REDUCED ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 struct mlx5dr_ste* list_prev_entry (struct mlx5dr_ste*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  miss_list_node ; 
 int /*<<< orphan*/  mlx5dr_send_fill_and_append_ste_send_info (struct mlx5dr_ste*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlx5dr_ste_send_info*,struct list_head*,int) ; 
 int /*<<< orphan*/  mlx5dr_ste_get_miss_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5dr_ste_set_miss_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dr_ste_remove_middle_ste(struct mlx5dr_ste *ste,
				     struct mlx5dr_ste_send_info *ste_info,
				     struct list_head *send_ste_list,
				     struct mlx5dr_ste_htbl *stats_tbl)
{
	struct mlx5dr_ste *prev_ste;
	u64 miss_addr;

	prev_ste = list_prev_entry(ste, miss_list_node);
	if (WARN_ON(!prev_ste))
		return;

	miss_addr = mlx5dr_ste_get_miss_addr(ste->hw_ste);
	mlx5dr_ste_set_miss_addr(prev_ste->hw_ste, miss_addr);

	mlx5dr_send_fill_and_append_ste_send_info(prev_ste, DR_STE_SIZE_REDUCED, 0,
						  prev_ste->hw_ste, ste_info,
						  send_ste_list, true /* Copy data*/);

	list_del_init(&ste->miss_list_node);

	stats_tbl->ctrl.num_of_valid_entries--;
	stats_tbl->ctrl.num_of_collisions--;
}