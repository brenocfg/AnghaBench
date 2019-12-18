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
struct mlx5_fc_bulk {int bulk_len; struct mlx5_fc* fcs; int /*<<< orphan*/  bitmask; } ;
struct mlx5_fc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSPC ; 
 struct mlx5_fc* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int find_first_bit (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct mlx5_fc *mlx5_fc_bulk_acquire_fc(struct mlx5_fc_bulk *bulk)
{
	int free_fc_index = find_first_bit(bulk->bitmask, bulk->bulk_len);

	if (free_fc_index >= bulk->bulk_len)
		return ERR_PTR(-ENOSPC);

	clear_bit(free_fc_index, bulk->bitmask);
	return &bulk->fcs[free_fc_index];
}