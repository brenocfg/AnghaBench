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
struct mlx5dr_matcher_rx_tx {void* e_anchor; void* s_htbl; TYPE_2__* ste_builder; TYPE_2__* ste_builder6; TYPE_2__* ste_builder4; } ;
struct mlx5dr_matcher {TYPE_1__* tbl; } ;
struct mlx5dr_domain {int /*<<< orphan*/  ste_icm_pool; } ;
struct TYPE_4__ {int /*<<< orphan*/  byte_mask; int /*<<< orphan*/  lu_type; } ;
struct TYPE_3__ {struct mlx5dr_domain* dmn; } ;

/* Variables and functions */
 int /*<<< orphan*/  DR_CHUNK_SIZE_1 ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MLX5DR_STE_LU_TYPE_DONT_CARE ; 
 int dr_matcher_set_ste_builders (struct mlx5dr_matcher*,struct mlx5dr_matcher_rx_tx*,int) ; 
 int /*<<< orphan*/  mlx5dr_dbg (struct mlx5dr_domain*,char*) ; 
 int /*<<< orphan*/  mlx5dr_htbl_get (void*) ; 
 void* mlx5dr_ste_htbl_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5dr_ste_htbl_free (void*) ; 

__attribute__((used)) static int dr_matcher_init_nic(struct mlx5dr_matcher *matcher,
			       struct mlx5dr_matcher_rx_tx *nic_matcher)
{
	struct mlx5dr_domain *dmn = matcher->tbl->dmn;
	int ret, ret_v4, ret_v6;

	ret_v4 = dr_matcher_set_ste_builders(matcher, nic_matcher, false);
	ret_v6 = dr_matcher_set_ste_builders(matcher, nic_matcher, true);

	if (ret_v4 && ret_v6) {
		mlx5dr_dbg(dmn, "Cannot generate IPv4 or IPv6 rules with given mask\n");
		return -EINVAL;
	}

	if (!ret_v4)
		nic_matcher->ste_builder = nic_matcher->ste_builder4;
	else
		nic_matcher->ste_builder = nic_matcher->ste_builder6;

	nic_matcher->e_anchor = mlx5dr_ste_htbl_alloc(dmn->ste_icm_pool,
						      DR_CHUNK_SIZE_1,
						      MLX5DR_STE_LU_TYPE_DONT_CARE,
						      0);
	if (!nic_matcher->e_anchor)
		return -ENOMEM;

	nic_matcher->s_htbl = mlx5dr_ste_htbl_alloc(dmn->ste_icm_pool,
						    DR_CHUNK_SIZE_1,
						    nic_matcher->ste_builder[0].lu_type,
						    nic_matcher->ste_builder[0].byte_mask);
	if (!nic_matcher->s_htbl) {
		ret = -ENOMEM;
		goto free_e_htbl;
	}

	/* make sure the tables exist while empty */
	mlx5dr_htbl_get(nic_matcher->s_htbl);
	mlx5dr_htbl_get(nic_matcher->e_anchor);

	return 0;

free_e_htbl:
	mlx5dr_ste_htbl_free(nic_matcher->e_anchor);
	return ret;
}