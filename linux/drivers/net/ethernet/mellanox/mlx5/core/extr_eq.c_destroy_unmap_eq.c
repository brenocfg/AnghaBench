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
struct mlx5_eq {int /*<<< orphan*/  buf; int /*<<< orphan*/  irqn; int /*<<< orphan*/  eqn; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_buf_free (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 
 int mlx5_cmd_destroy_eq (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_debug_eq_remove (struct mlx5_core_dev*,struct mlx5_eq*) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int destroy_unmap_eq(struct mlx5_core_dev *dev, struct mlx5_eq *eq)
{
	int err;

	mlx5_debug_eq_remove(dev, eq);

	err = mlx5_cmd_destroy_eq(dev, eq->eqn);
	if (err)
		mlx5_core_warn(dev, "failed to destroy a previously created eq: eqn %d\n",
			       eq->eqn);
	synchronize_irq(eq->irqn);

	mlx5_buf_free(dev, &eq->buf);

	return err;
}