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
struct mlx5dr_send_ring {struct mlx5dr_send_ring* buf; int /*<<< orphan*/  mr; int /*<<< orphan*/  sync_mr; int /*<<< orphan*/  cq; int /*<<< orphan*/  qp; } ;
struct mlx5dr_domain {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dr_dereg_mr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dr_destroy_cq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dr_destroy_qp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx5dr_send_ring*) ; 

void mlx5dr_send_ring_free(struct mlx5dr_domain *dmn,
			   struct mlx5dr_send_ring *send_ring)
{
	dr_destroy_qp(dmn->mdev, send_ring->qp);
	dr_destroy_cq(dmn->mdev, send_ring->cq);
	dr_dereg_mr(dmn->mdev, send_ring->sync_mr);
	dr_dereg_mr(dmn->mdev, send_ring->mr);
	kfree(send_ring->buf);
	kfree(send_ring);
}