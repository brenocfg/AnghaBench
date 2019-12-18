#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct mlx5dr_ste_build {int (* ste_build_tag_func ) (struct mlx5dr_match_param*,struct mlx5dr_ste_build*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  byte_mask; int /*<<< orphan*/  lu_type; int /*<<< orphan*/  bit_mask; } ;
struct mlx5dr_matcher_rx_tx {int num_of_builders; struct mlx5dr_ste_build* ste_builder; TYPE_1__* nic_tbl; } ;
struct mlx5dr_matcher {int /*<<< orphan*/  mask; int /*<<< orphan*/  match_criteria; TYPE_2__* tbl; } ;
struct mlx5dr_match_param {int dummy; } ;
struct mlx5dr_domain_rx_tx {int /*<<< orphan*/  ste_type; } ;
struct TYPE_7__ {int /*<<< orphan*/  gvmi; } ;
struct TYPE_8__ {TYPE_3__ caps; } ;
struct mlx5dr_domain {TYPE_4__ info; } ;
struct TYPE_6__ {struct mlx5dr_domain* dmn; } ;
struct TYPE_5__ {struct mlx5dr_domain_rx_tx* nic_dmn; } ;

/* Variables and functions */
 int /*<<< orphan*/  DR_STE_SIZE ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  byte_mask ; 
 int mlx5dr_ste_build_pre_check (struct mlx5dr_domain*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mlx5dr_match_param*) ; 
 int /*<<< orphan*/  mlx5dr_ste_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5dr_ste_set_bit_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next_lu_type ; 
 int /*<<< orphan*/  ste_general ; 
 int stub1 (struct mlx5dr_match_param*,struct mlx5dr_ste_build*,int /*<<< orphan*/ *) ; 

int mlx5dr_ste_build_ste_arr(struct mlx5dr_matcher *matcher,
			     struct mlx5dr_matcher_rx_tx *nic_matcher,
			     struct mlx5dr_match_param *value,
			     u8 *ste_arr)
{
	struct mlx5dr_domain_rx_tx *nic_dmn = nic_matcher->nic_tbl->nic_dmn;
	struct mlx5dr_domain *dmn = matcher->tbl->dmn;
	struct mlx5dr_ste_build *sb;
	int ret, i;

	ret = mlx5dr_ste_build_pre_check(dmn, matcher->match_criteria,
					 &matcher->mask, value);
	if (ret)
		return ret;

	sb = nic_matcher->ste_builder;
	for (i = 0; i < nic_matcher->num_of_builders; i++) {
		mlx5dr_ste_init(ste_arr,
				sb->lu_type,
				nic_dmn->ste_type,
				dmn->info.caps.gvmi);

		mlx5dr_ste_set_bit_mask(ste_arr, sb->bit_mask);

		ret = sb->ste_build_tag_func(value, sb, ste_arr);
		if (ret)
			return ret;

		/* Connect the STEs */
		if (i < (nic_matcher->num_of_builders - 1)) {
			/* Need the next builder for these fields,
			 * not relevant for the last ste in the chain.
			 */
			sb++;
			MLX5_SET(ste_general, ste_arr, next_lu_type, sb->lu_type);
			MLX5_SET(ste_general, ste_arr, byte_mask, sb->byte_mask);
		}
		ste_arr += DR_STE_SIZE;
	}
	return 0;
}