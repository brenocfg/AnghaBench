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
struct mlx5dr_ste_htbl {int chunk_size; } ;
struct mlx5dr_rule_rx_tx {int dummy; } ;
struct mlx5dr_rule {TYPE_2__* matcher; } ;
struct TYPE_6__ {int /*<<< orphan*/  max_log_sw_icm_sz; } ;
struct mlx5dr_domain {TYPE_3__ info; } ;
struct list_head {int dummy; } ;
typedef  enum mlx5dr_icm_chunk_size { ____Placeholder_mlx5dr_icm_chunk_size } mlx5dr_icm_chunk_size ;
struct TYPE_5__ {TYPE_1__* tbl; } ;
struct TYPE_4__ {struct mlx5dr_domain* dmn; } ;

/* Variables and functions */
 struct mlx5dr_ste_htbl* dr_rule_rehash_htbl (struct mlx5dr_rule*,struct mlx5dr_rule_rx_tx*,struct mlx5dr_ste_htbl*,int /*<<< orphan*/ ,struct list_head*,int) ; 
 int min_t (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int mlx5dr_icm_next_higher_chunk (int) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static struct mlx5dr_ste_htbl *dr_rule_rehash(struct mlx5dr_rule *rule,
					      struct mlx5dr_rule_rx_tx *nic_rule,
					      struct mlx5dr_ste_htbl *cur_htbl,
					      u8 ste_location,
					      struct list_head *update_list)
{
	struct mlx5dr_domain *dmn = rule->matcher->tbl->dmn;
	enum mlx5dr_icm_chunk_size new_size;

	new_size = mlx5dr_icm_next_higher_chunk(cur_htbl->chunk_size);
	new_size = min_t(u32, new_size, dmn->info.max_log_sw_icm_sz);

	if (new_size == cur_htbl->chunk_size)
		return NULL; /* Skip rehash, we already at the max size */

	return dr_rule_rehash_htbl(rule, nic_rule, cur_htbl, ste_location,
				   update_list, new_size);
}