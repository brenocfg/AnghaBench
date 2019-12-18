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
typedef  int /*<<< orphan*/  u8 ;
struct mlx5dr_ste_htbl {struct mlx5dr_icm_chunk* chunk; } ;
struct mlx5dr_icm_chunk {int /*<<< orphan*/  num_of_entries; int /*<<< orphan*/  icm_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5dr_ste_set_hit_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mlx5dr_ste_set_hit_addr_by_next_htbl(u8 *hw_ste,
					  struct mlx5dr_ste_htbl *next_htbl)
{
	struct mlx5dr_icm_chunk *chunk = next_htbl->chunk;

	mlx5dr_ste_set_hit_addr(hw_ste, chunk->icm_addr, chunk->num_of_entries);
}