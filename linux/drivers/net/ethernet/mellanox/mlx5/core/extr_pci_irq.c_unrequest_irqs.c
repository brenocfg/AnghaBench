#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx5_irq_table {int nvec; } ;
struct TYPE_3__ {struct mlx5_irq_table* irq_table; } ;
struct mlx5_core_dev {int /*<<< orphan*/  pdev; TYPE_1__ priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  nh; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* mlx5_irq_get (struct mlx5_core_dev*,int) ; 
 int /*<<< orphan*/  pci_irq_vector (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void unrequest_irqs(struct mlx5_core_dev *dev)
{
	struct mlx5_irq_table *table = dev->priv.irq_table;
	int i;

	for (i = 0; i < table->nvec; i++)
		free_irq(pci_irq_vector(dev->pdev, i),
			 &mlx5_irq_get(dev, i)->nh);
}