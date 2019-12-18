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
struct mlx5_core_dev {int /*<<< orphan*/  vsc_addr; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_CAP_ID_VNDR ; 
 int /*<<< orphan*/  mlx5_core_is_pf (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*) ; 
 int /*<<< orphan*/  pci_find_capability (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mlx5_pci_vsc_init(struct mlx5_core_dev *dev)
{
	if (!mlx5_core_is_pf(dev))
		return;

	dev->vsc_addr = pci_find_capability(dev->pdev,
					    PCI_CAP_ID_VNDR);
	if (!dev->vsc_addr)
		mlx5_core_warn(dev, "Failed to get valid vendor specific ID\n");
}