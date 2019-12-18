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
struct pci_dev {int dummy; } ;
struct mlx4_dev {TYPE_1__* persist; } ;
struct TYPE_2__ {scalar_t__ pci_status; int /*<<< orphan*/  pci_status_mutex; struct pci_dev* pdev; } ;

/* Variables and functions */
 scalar_t__ MLX4_PCI_STATUS_DISABLED ; 
 scalar_t__ MLX4_PCI_STATUS_ENABLED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pci_enable_device (struct pci_dev*) ; 

__attribute__((used)) static int mlx4_pci_enable_device(struct mlx4_dev *dev)
{
	struct pci_dev *pdev = dev->persist->pdev;
	int err = 0;

	mutex_lock(&dev->persist->pci_status_mutex);
	if (dev->persist->pci_status == MLX4_PCI_STATUS_DISABLED) {
		err = pci_enable_device(pdev);
		if (!err)
			dev->persist->pci_status = MLX4_PCI_STATUS_ENABLED;
	}
	mutex_unlock(&dev->persist->pci_status_mutex);

	return err;
}