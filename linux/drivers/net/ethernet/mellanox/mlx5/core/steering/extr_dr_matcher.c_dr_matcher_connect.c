#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx5dr_table_rx_tx {struct mlx5dr_ste_htbl* s_anchor; int /*<<< orphan*/  default_icm_addr; struct mlx5dr_domain_rx_tx* nic_dmn; } ;
struct mlx5dr_ste_htbl {TYPE_2__* ste_arr; TYPE_2__* pointing_ste; TYPE_1__* chunk; } ;
struct mlx5dr_matcher_rx_tx {struct mlx5dr_ste_htbl* s_htbl; struct mlx5dr_ste_htbl* e_anchor; struct mlx5dr_table_rx_tx* nic_tbl; } ;
struct mlx5dr_htbl_connect_info {scalar_t__ type; struct mlx5dr_ste_htbl* hit_next_htbl; int /*<<< orphan*/  miss_icm_addr; } ;
struct mlx5dr_domain_rx_tx {int dummy; } ;
struct mlx5dr_domain {int dummy; } ;
struct TYPE_4__ {struct mlx5dr_ste_htbl* next_htbl; } ;
struct TYPE_3__ {int /*<<< orphan*/  icm_addr; } ;

/* Variables and functions */
 scalar_t__ CONNECT_HIT ; 
 void* CONNECT_MISS ; 
 int mlx5dr_ste_htbl_init_and_postsend (struct mlx5dr_domain*,struct mlx5dr_domain_rx_tx*,struct mlx5dr_ste_htbl*,struct mlx5dr_htbl_connect_info*,int) ; 

__attribute__((used)) static int dr_matcher_connect(struct mlx5dr_domain *dmn,
			      struct mlx5dr_matcher_rx_tx *curr_nic_matcher,
			      struct mlx5dr_matcher_rx_tx *next_nic_matcher,
			      struct mlx5dr_matcher_rx_tx *prev_nic_matcher)
{
	struct mlx5dr_table_rx_tx *nic_tbl = curr_nic_matcher->nic_tbl;
	struct mlx5dr_domain_rx_tx *nic_dmn = nic_tbl->nic_dmn;
	struct mlx5dr_htbl_connect_info info;
	struct mlx5dr_ste_htbl *prev_htbl;
	int ret;

	/* Connect end anchor hash table to next_htbl or to the default address */
	if (next_nic_matcher) {
		info.type = CONNECT_HIT;
		info.hit_next_htbl = next_nic_matcher->s_htbl;
	} else {
		info.type = CONNECT_MISS;
		info.miss_icm_addr = nic_tbl->default_icm_addr;
	}
	ret = mlx5dr_ste_htbl_init_and_postsend(dmn, nic_dmn,
						curr_nic_matcher->e_anchor,
						&info, info.type == CONNECT_HIT);
	if (ret)
		return ret;

	/* Connect start hash table to end anchor */
	info.type = CONNECT_MISS;
	info.miss_icm_addr = curr_nic_matcher->e_anchor->chunk->icm_addr;
	ret = mlx5dr_ste_htbl_init_and_postsend(dmn, nic_dmn,
						curr_nic_matcher->s_htbl,
						&info, false);
	if (ret)
		return ret;

	/* Connect previous hash table to matcher start hash table */
	if (prev_nic_matcher)
		prev_htbl = prev_nic_matcher->e_anchor;
	else
		prev_htbl = nic_tbl->s_anchor;

	info.type = CONNECT_HIT;
	info.hit_next_htbl = curr_nic_matcher->s_htbl;
	ret = mlx5dr_ste_htbl_init_and_postsend(dmn, nic_dmn, prev_htbl,
						&info, true);
	if (ret)
		return ret;

	/* Update the pointing ste and next hash table */
	curr_nic_matcher->s_htbl->pointing_ste = prev_htbl->ste_arr;
	prev_htbl->ste_arr[0].next_htbl = curr_nic_matcher->s_htbl;

	if (next_nic_matcher) {
		next_nic_matcher->s_htbl->pointing_ste = curr_nic_matcher->e_anchor->ste_arr;
		curr_nic_matcher->e_anchor->ste_arr[0].next_htbl = next_nic_matcher->s_htbl;
	}

	return 0;
}