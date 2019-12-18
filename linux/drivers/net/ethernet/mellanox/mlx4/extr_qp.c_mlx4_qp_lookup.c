#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mlx4_qp_table {int /*<<< orphan*/  lock; } ;
struct mlx4_qp {int dummy; } ;
struct mlx4_dev {int dummy; } ;
struct TYPE_2__ {struct mlx4_qp_table qp_table; } ;

/* Variables and functions */
 struct mlx4_qp* __mlx4_qp_lookup (struct mlx4_dev*,int /*<<< orphan*/ ) ; 
 TYPE_1__* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

struct mlx4_qp *mlx4_qp_lookup(struct mlx4_dev *dev, u32 qpn)
{
	struct mlx4_qp_table *qp_table = &mlx4_priv(dev)->qp_table;
	struct mlx4_qp *qp;

	spin_lock_irq(&qp_table->lock);

	qp = __mlx4_qp_lookup(dev, qpn);

	spin_unlock_irq(&qp_table->lock);
	return qp;
}