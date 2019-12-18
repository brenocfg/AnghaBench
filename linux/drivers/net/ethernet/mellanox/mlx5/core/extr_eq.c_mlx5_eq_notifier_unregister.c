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
struct mlx5_nb {size_t event_type; int /*<<< orphan*/  nb; } ;
struct mlx5_eq_table {int /*<<< orphan*/ * nh; } ;
struct TYPE_2__ {struct mlx5_eq_table* eq_table; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int atomic_notifier_chain_unregister (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int mlx5_eq_notifier_unregister(struct mlx5_core_dev *dev, struct mlx5_nb *nb)
{
	struct mlx5_eq_table *eqt = dev->priv.eq_table;

	return atomic_notifier_chain_unregister(&eqt->nh[nb->event_type], &nb->nb);
}