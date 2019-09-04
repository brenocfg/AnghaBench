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
struct mlx5e_icosq {int /*<<< orphan*/  wq_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_wq_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_free_icosq_db (struct mlx5e_icosq*) ; 

__attribute__((used)) static void mlx5e_free_icosq(struct mlx5e_icosq *sq)
{
	mlx5e_free_icosq_db(sq);
	mlx5_wq_destroy(&sq->wq_ctrl);
}