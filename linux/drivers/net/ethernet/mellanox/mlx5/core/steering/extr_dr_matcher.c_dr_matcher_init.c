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
struct mlx5dr_table {int /*<<< orphan*/  tx; int /*<<< orphan*/  rx; struct mlx5dr_domain* dmn; } ;
struct TYPE_2__ {int /*<<< orphan*/ * nic_tbl; } ;
struct mlx5dr_matcher {scalar_t__ match_criteria; TYPE_1__ tx; TYPE_1__ rx; int /*<<< orphan*/  mask; struct mlx5dr_table* tbl; } ;
struct mlx5dr_match_parameters {int match_sz; } ;
struct mlx5dr_match_param {int dummy; } ;
struct mlx5dr_domain {int type; } ;

/* Variables and functions */
 scalar_t__ DR_MATCHER_CRITERIA_MAX ; 
 int EINVAL ; 
#define  MLX5DR_DOMAIN_TYPE_FDB 130 
#define  MLX5DR_DOMAIN_TYPE_NIC_RX 129 
#define  MLX5DR_DOMAIN_TYPE_NIC_TX 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int dr_matcher_init_fdb (struct mlx5dr_matcher*) ; 
 int dr_matcher_init_nic (struct mlx5dr_matcher*,TYPE_1__*) ; 
 int /*<<< orphan*/  mlx5dr_info (struct mlx5dr_domain*,char*) ; 
 int /*<<< orphan*/  mlx5dr_ste_copy_param (scalar_t__,int /*<<< orphan*/ *,struct mlx5dr_match_parameters*) ; 

__attribute__((used)) static int dr_matcher_init(struct mlx5dr_matcher *matcher,
			   struct mlx5dr_match_parameters *mask)
{
	struct mlx5dr_table *tbl = matcher->tbl;
	struct mlx5dr_domain *dmn = tbl->dmn;
	int ret;

	if (matcher->match_criteria >= DR_MATCHER_CRITERIA_MAX) {
		mlx5dr_info(dmn, "Invalid match criteria attribute\n");
		return -EINVAL;
	}

	if (mask) {
		if (mask->match_sz > sizeof(struct mlx5dr_match_param)) {
			mlx5dr_info(dmn, "Invalid match size attribute\n");
			return -EINVAL;
		}
		mlx5dr_ste_copy_param(matcher->match_criteria,
				      &matcher->mask, mask);
	}

	switch (dmn->type) {
	case MLX5DR_DOMAIN_TYPE_NIC_RX:
		matcher->rx.nic_tbl = &tbl->rx;
		ret = dr_matcher_init_nic(matcher, &matcher->rx);
		break;
	case MLX5DR_DOMAIN_TYPE_NIC_TX:
		matcher->tx.nic_tbl = &tbl->tx;
		ret = dr_matcher_init_nic(matcher, &matcher->tx);
		break;
	case MLX5DR_DOMAIN_TYPE_FDB:
		matcher->rx.nic_tbl = &tbl->rx;
		matcher->tx.nic_tbl = &tbl->tx;
		ret = dr_matcher_init_fdb(matcher);
		break;
	default:
		WARN_ON(true);
		return -EINVAL;
	}

	return ret;
}