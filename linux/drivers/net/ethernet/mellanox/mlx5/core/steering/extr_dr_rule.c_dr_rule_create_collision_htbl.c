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
struct mlx5dr_ste_htbl {struct mlx5dr_ste* ste_arr; } ;
struct mlx5dr_ste {int dummy; } ;
struct mlx5dr_matcher_rx_tx {TYPE_1__* e_anchor; } ;
struct mlx5dr_matcher {TYPE_2__* tbl; } ;
struct mlx5dr_domain {int /*<<< orphan*/  ste_icm_pool; } ;
struct TYPE_6__ {int /*<<< orphan*/  icm_addr; } ;
struct TYPE_5__ {struct mlx5dr_domain* dmn; } ;
struct TYPE_4__ {TYPE_3__* chunk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DR_CHUNK_SIZE_1 ; 
 int /*<<< orphan*/  MLX5DR_STE_LU_TYPE_DONT_CARE ; 
 int /*<<< orphan*/  mlx5dr_dbg (struct mlx5dr_domain*,char*) ; 
 int /*<<< orphan*/  mlx5dr_htbl_get (struct mlx5dr_ste_htbl*) ; 
 struct mlx5dr_ste_htbl* mlx5dr_ste_htbl_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5dr_ste_set_miss_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlx5dr_ste *
dr_rule_create_collision_htbl(struct mlx5dr_matcher *matcher,
			      struct mlx5dr_matcher_rx_tx *nic_matcher,
			      u8 *hw_ste)
{
	struct mlx5dr_domain *dmn = matcher->tbl->dmn;
	struct mlx5dr_ste_htbl *new_htbl;
	struct mlx5dr_ste *ste;

	/* Create new table for miss entry */
	new_htbl = mlx5dr_ste_htbl_alloc(dmn->ste_icm_pool,
					 DR_CHUNK_SIZE_1,
					 MLX5DR_STE_LU_TYPE_DONT_CARE,
					 0);
	if (!new_htbl) {
		mlx5dr_dbg(dmn, "Failed allocating collision table\n");
		return NULL;
	}

	/* One and only entry, never grows */
	ste = new_htbl->ste_arr;
	mlx5dr_ste_set_miss_addr(hw_ste, nic_matcher->e_anchor->chunk->icm_addr);
	mlx5dr_htbl_get(new_htbl);

	return ste;
}