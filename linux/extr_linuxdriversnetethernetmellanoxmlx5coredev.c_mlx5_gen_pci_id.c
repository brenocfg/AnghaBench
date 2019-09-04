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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_core_dev {TYPE_1__* pdev; } ;
struct TYPE_4__ {int number; } ;
struct TYPE_3__ {int /*<<< orphan*/  devfn; TYPE_2__* bus; } ;

/* Variables and functions */
 int PCI_SLOT (int /*<<< orphan*/ ) ; 
 int pci_domain_nr (TYPE_2__*) ; 

__attribute__((used)) static u32 mlx5_gen_pci_id(struct mlx5_core_dev *dev)
{
	return (u32)((pci_domain_nr(dev->pdev->bus) << 16) |
		     (dev->pdev->bus->number << 8) |
		     PCI_SLOT(dev->pdev->devfn));
}