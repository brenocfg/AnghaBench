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
struct mlx5dr_ste_htbl {struct mlx5dr_ste* ste_arr; int /*<<< orphan*/  chunk_size; } ;
struct mlx5dr_ste {int dummy; } ;
struct mlx5dr_matcher_rx_tx {int dummy; } ;
struct mlx5dr_matcher {TYPE_1__* tbl; } ;
struct list_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dmn; } ;

/* Variables and functions */
 int EINVAL ; 
 int dr_rule_rehash_copy_miss_list (struct mlx5dr_matcher*,struct mlx5dr_matcher_rx_tx*,int /*<<< orphan*/ ,struct mlx5dr_ste_htbl*,struct list_head*) ; 
 int /*<<< orphan*/  mlx5dr_dbg (int /*<<< orphan*/ ,char*) ; 
 int mlx5dr_icm_pool_chunk_size_to_entries (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5dr_ste_get_miss_list (struct mlx5dr_ste*) ; 
 scalar_t__ mlx5dr_ste_not_used_ste (struct mlx5dr_ste*) ; 

__attribute__((used)) static int dr_rule_rehash_copy_htbl(struct mlx5dr_matcher *matcher,
				    struct mlx5dr_matcher_rx_tx *nic_matcher,
				    struct mlx5dr_ste_htbl *cur_htbl,
				    struct mlx5dr_ste_htbl *new_htbl,
				    struct list_head *update_list)
{
	struct mlx5dr_ste *cur_ste;
	int cur_entries;
	int err = 0;
	int i;

	cur_entries = mlx5dr_icm_pool_chunk_size_to_entries(cur_htbl->chunk_size);

	if (cur_entries < 1) {
		mlx5dr_dbg(matcher->tbl->dmn, "Invalid number of entries\n");
		return -EINVAL;
	}

	for (i = 0; i < cur_entries; i++) {
		cur_ste = &cur_htbl->ste_arr[i];
		if (mlx5dr_ste_not_used_ste(cur_ste)) /* Empty, nothing to copy */
			continue;

		err = dr_rule_rehash_copy_miss_list(matcher,
						    nic_matcher,
						    mlx5dr_ste_get_miss_list(cur_ste),
						    new_htbl,
						    update_list);
		if (err)
			goto clean_copy;
	}

clean_copy:
	return err;
}