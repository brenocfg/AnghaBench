#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mlx5dr_ste_htbl_ctrl {int may_grow; int increase_threshold; } ;
struct mlx5dr_ste_htbl {int chunk_size; struct mlx5dr_ste_htbl_ctrl ctrl; } ;

/* Variables and functions */
 int DR_CHUNK_SIZE_MAX ; 
 int mlx5dr_icm_pool_chunk_size_to_entries (int) ; 

__attribute__((used)) static void dr_ste_set_ctrl(struct mlx5dr_ste_htbl *htbl)
{
	struct mlx5dr_ste_htbl_ctrl *ctrl = &htbl->ctrl;
	int num_of_entries;

	htbl->ctrl.may_grow = true;

	if (htbl->chunk_size == DR_CHUNK_SIZE_MAX - 1)
		htbl->ctrl.may_grow = false;

	/* Threshold is 50%, one is added to table of size 1 */
	num_of_entries = mlx5dr_icm_pool_chunk_size_to_entries(htbl->chunk_size);
	ctrl->increase_threshold = (num_of_entries + 1) / 2;
}