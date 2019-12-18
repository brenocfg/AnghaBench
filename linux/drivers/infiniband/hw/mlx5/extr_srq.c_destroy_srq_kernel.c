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
struct mlx5_ib_srq {int /*<<< orphan*/  db; int /*<<< orphan*/  buf; int /*<<< orphan*/  wrid; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_db_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_frag_buf_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_srq_kernel(struct mlx5_ib_dev *dev, struct mlx5_ib_srq *srq)
{
	kvfree(srq->wrid);
	mlx5_frag_buf_free(dev->mdev, &srq->buf);
	mlx5_db_free(dev->mdev, &srq->db);
}