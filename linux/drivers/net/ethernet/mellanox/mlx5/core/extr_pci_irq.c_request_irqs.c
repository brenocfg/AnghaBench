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
struct mlx5_irq {int /*<<< orphan*/  nh; int /*<<< orphan*/  name; } ;
struct mlx5_core_dev {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_INIT_NOTIFIER_HEAD (int /*<<< orphan*/ *) ; 
 int MLX5_MAX_IRQ_NAME ; 
 int /*<<< orphan*/  free_irq (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_name (char*,int) ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*) ; 
 struct mlx5_irq* mlx5_irq_get (struct mlx5_core_dev*,int) ; 
 int /*<<< orphan*/  mlx5_irq_int_handler ; 
 int pci_irq_vector (int /*<<< orphan*/ ,int) ; 
 char* pci_name (int /*<<< orphan*/ ) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char*) ; 

__attribute__((used)) static int request_irqs(struct mlx5_core_dev *dev, int nvec)
{
	char name[MLX5_MAX_IRQ_NAME];
	int err;
	int i;

	for (i = 0; i < nvec; i++) {
		struct mlx5_irq *irq = mlx5_irq_get(dev, i);
		int irqn = pci_irq_vector(dev->pdev, i);

		irq_set_name(name, i);
		ATOMIC_INIT_NOTIFIER_HEAD(&irq->nh);
		snprintf(irq->name, MLX5_MAX_IRQ_NAME,
			 "%s@pci:%s", name, pci_name(dev->pdev));
		err = request_irq(irqn, mlx5_irq_int_handler, 0, irq->name,
				  &irq->nh);
		if (err) {
			mlx5_core_err(dev, "Failed to request irq\n");
			goto err_request_irq;
		}
	}
	return 0;

err_request_irq:
	for (; i >= 0; i--) {
		struct mlx5_irq *irq = mlx5_irq_get(dev, i);
		int irqn = pci_irq_vector(dev->pdev, i);

		free_irq(irqn, &irq->nh);
	}
	return  err;
}