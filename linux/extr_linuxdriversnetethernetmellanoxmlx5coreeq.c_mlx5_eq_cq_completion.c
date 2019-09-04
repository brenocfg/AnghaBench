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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_eq {int /*<<< orphan*/  dev; } ;
struct mlx5_core_cq {int /*<<< orphan*/  (* comp ) (struct mlx5_core_cq*) ;int /*<<< orphan*/  arm_sn; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_core_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_cq_put (struct mlx5_core_cq*) ; 
 struct mlx5_core_cq* mlx5_eq_cq_get (struct mlx5_eq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mlx5_core_cq*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void mlx5_eq_cq_completion(struct mlx5_eq *eq, u32 cqn)
{
	struct mlx5_core_cq *cq = mlx5_eq_cq_get(eq, cqn);

	if (unlikely(!cq)) {
		mlx5_core_warn(eq->dev, "Completion event for bogus CQ 0x%x\n", cqn);
		return;
	}

	++cq->arm_sn;

	cq->comp(cq);

	mlx5_cq_put(cq);
}