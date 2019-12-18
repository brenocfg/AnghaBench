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
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct mlx5_ib_cq {int /*<<< orphan*/  db; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_cq_buf (struct mlx5_ib_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_db_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_cq_kernel(struct mlx5_ib_dev *dev, struct mlx5_ib_cq *cq)
{
	free_cq_buf(dev, &cq->buf);
	mlx5_db_free(dev->mdev, &cq->db);
}