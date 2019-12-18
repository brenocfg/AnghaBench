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
struct mlx5dr_cq {int /*<<< orphan*/  wq; } ;
struct mlx5_cqe64 {int dummy; } ;

/* Variables and functions */
 int CQ_EMPTY ; 
 int dr_parse_cqe (struct mlx5dr_cq*,struct mlx5_cqe64*) ; 
 struct mlx5_cqe64* mlx5_cqwq_get_cqe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_cqwq_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_cqwq_update_db_record (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dr_cq_poll_one(struct mlx5dr_cq *dr_cq)
{
	struct mlx5_cqe64 *cqe64;
	int err;

	cqe64 = mlx5_cqwq_get_cqe(&dr_cq->wq);
	if (!cqe64)
		return CQ_EMPTY;

	mlx5_cqwq_pop(&dr_cq->wq);
	err = dr_parse_cqe(dr_cq, cqe64);
	mlx5_cqwq_update_db_record(&dr_cq->wq);

	return err;
}