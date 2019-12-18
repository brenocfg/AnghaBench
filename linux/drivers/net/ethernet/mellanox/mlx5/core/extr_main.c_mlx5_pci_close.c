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
struct mlx5_core_dev {int /*<<< orphan*/  pdev; int /*<<< orphan*/  iseg; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_pci_disable_device (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  pci_clear_master (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_bar (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5_pci_close(struct mlx5_core_dev *dev)
{
	iounmap(dev->iseg);
	pci_clear_master(dev->pdev);
	release_bar(dev->pdev);
	mlx5_pci_disable_device(dev);
}