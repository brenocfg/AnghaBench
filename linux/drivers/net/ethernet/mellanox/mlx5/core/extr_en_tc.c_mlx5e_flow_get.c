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
struct mlx5e_tc_flow {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct mlx5e_tc_flow* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mlx5e_tc_flow *mlx5e_flow_get(struct mlx5e_tc_flow *flow)
{
	if (!flow || !refcount_inc_not_zero(&flow->refcnt))
		return ERR_PTR(-EINVAL);
	return flow;
}