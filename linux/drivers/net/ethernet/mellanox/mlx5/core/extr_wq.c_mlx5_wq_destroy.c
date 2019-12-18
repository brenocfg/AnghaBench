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
struct mlx5_wq_ctrl {int /*<<< orphan*/  db; int /*<<< orphan*/  mdev; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_db_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_frag_buf_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void mlx5_wq_destroy(struct mlx5_wq_ctrl *wq_ctrl)
{
	mlx5_frag_buf_free(wq_ctrl->mdev, &wq_ctrl->buf);
	mlx5_db_free(wq_ctrl->mdev, &wq_ctrl->db);
}