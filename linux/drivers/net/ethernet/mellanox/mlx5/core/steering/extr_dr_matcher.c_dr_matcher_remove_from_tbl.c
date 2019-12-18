#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx5dr_table {int /*<<< orphan*/  tx; int /*<<< orphan*/  rx; int /*<<< orphan*/  matcher_list; struct mlx5dr_domain* dmn; } ;
struct TYPE_3__ {int /*<<< orphan*/ * prev; } ;
struct mlx5dr_matcher {TYPE_1__ matcher_list; int /*<<< orphan*/  tx; int /*<<< orphan*/  rx; struct mlx5dr_table* tbl; } ;
struct mlx5dr_domain {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ MLX5DR_DOMAIN_TYPE_FDB ; 
 scalar_t__ MLX5DR_DOMAIN_TYPE_NIC_RX ; 
 scalar_t__ MLX5DR_DOMAIN_TYPE_NIC_TX ; 
 int dr_matcher_disconnect (struct mlx5dr_domain*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (TYPE_1__*) ; 
 scalar_t__ list_is_last (TYPE_1__*,int /*<<< orphan*/ *) ; 
 struct mlx5dr_matcher* list_next_entry (struct mlx5dr_matcher*,int /*<<< orphan*/ ) ; 
 struct mlx5dr_matcher* list_prev_entry (struct mlx5dr_matcher*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  matcher_list ; 

__attribute__((used)) static int dr_matcher_remove_from_tbl(struct mlx5dr_matcher *matcher)
{
	struct mlx5dr_matcher *prev_matcher, *next_matcher;
	struct mlx5dr_table *tbl = matcher->tbl;
	struct mlx5dr_domain *dmn = tbl->dmn;
	int ret = 0;

	if (list_is_last(&matcher->matcher_list, &tbl->matcher_list))
		next_matcher = NULL;
	else
		next_matcher = list_next_entry(matcher, matcher_list);

	if (matcher->matcher_list.prev == &tbl->matcher_list)
		prev_matcher = NULL;
	else
		prev_matcher = list_prev_entry(matcher, matcher_list);

	if (dmn->type == MLX5DR_DOMAIN_TYPE_FDB ||
	    dmn->type == MLX5DR_DOMAIN_TYPE_NIC_RX) {
		ret = dr_matcher_disconnect(dmn, &tbl->rx,
					    next_matcher ? &next_matcher->rx : NULL,
					    prev_matcher ? &prev_matcher->rx : NULL);
		if (ret)
			return ret;
	}

	if (dmn->type == MLX5DR_DOMAIN_TYPE_FDB ||
	    dmn->type == MLX5DR_DOMAIN_TYPE_NIC_TX) {
		ret = dr_matcher_disconnect(dmn, &tbl->tx,
					    next_matcher ? &next_matcher->tx : NULL,
					    prev_matcher ? &prev_matcher->tx : NULL);
		if (ret)
			return ret;
	}

	list_del(&matcher->matcher_list);

	return 0;
}