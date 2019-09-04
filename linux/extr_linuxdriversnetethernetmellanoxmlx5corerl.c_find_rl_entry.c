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
struct mlx5_rl_table {int max_size; struct mlx5_rl_entry* rl_entry; } ;
struct TYPE_2__ {int /*<<< orphan*/  rate; } ;
struct mlx5_rl_entry {TYPE_1__ rl; } ;
struct mlx5_rate_limit {int dummy; } ;

/* Variables and functions */
 scalar_t__ mlx5_rl_are_equal (TYPE_1__*,struct mlx5_rate_limit*) ; 

__attribute__((used)) static struct mlx5_rl_entry *find_rl_entry(struct mlx5_rl_table *table,
					   struct mlx5_rate_limit *rl)
{
	struct mlx5_rl_entry *ret_entry = NULL;
	bool empty_found = false;
	int i;

	for (i = 0; i < table->max_size; i++) {
		if (mlx5_rl_are_equal(&table->rl_entry[i].rl, rl))
			return &table->rl_entry[i];
		if (!empty_found && !table->rl_entry[i].rl.rate) {
			empty_found = true;
			ret_entry = &table->rl_entry[i];
		}
	}

	return ret_entry;
}