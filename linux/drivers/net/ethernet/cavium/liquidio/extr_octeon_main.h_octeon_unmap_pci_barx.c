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
struct octeon_device {TYPE_2__* pci_dev; TYPE_1__* mmio; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ start; int /*<<< orphan*/  hw_addr; scalar_t__ done; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_region (TYPE_2__*,int) ; 

__attribute__((used)) static inline void octeon_unmap_pci_barx(struct octeon_device *oct, int baridx)
{
	dev_dbg(&oct->pci_dev->dev, "Freeing PCI mapped regions for Bar%d\n",
		baridx);

	if (oct->mmio[baridx].done)
		iounmap(oct->mmio[baridx].hw_addr);

	if (oct->mmio[baridx].start)
		pci_release_region(oct->pci_dev, baridx * 2);
}