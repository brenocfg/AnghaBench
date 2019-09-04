#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct octeon_device {TYPE_2__* pci_dev; TYPE_1__* mmio; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int len; int mapped_len; int done; int /*<<< orphan*/  hw_addr; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_release_region (TYPE_2__*,int) ; 
 scalar_t__ pci_request_region (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int pci_resource_len (TYPE_2__*,int) ; 
 int /*<<< orphan*/  pci_resource_start (TYPE_2__*,int) ; 

__attribute__((used)) static inline int octeon_map_pci_barx(struct octeon_device *oct,
				      int baridx, int max_map_len)
{
	u32 mapped_len = 0;

	if (pci_request_region(oct->pci_dev, baridx * 2, DRV_NAME)) {
		dev_err(&oct->pci_dev->dev, "pci_request_region failed for bar %d\n",
			baridx);
		return 1;
	}

	oct->mmio[baridx].start = pci_resource_start(oct->pci_dev, baridx * 2);
	oct->mmio[baridx].len = pci_resource_len(oct->pci_dev, baridx * 2);

	mapped_len = oct->mmio[baridx].len;
	if (!mapped_len)
		goto err_release_region;

	if (max_map_len && (mapped_len > max_map_len))
		mapped_len = max_map_len;

	oct->mmio[baridx].hw_addr =
		ioremap(oct->mmio[baridx].start, mapped_len);
	oct->mmio[baridx].mapped_len = mapped_len;

	dev_dbg(&oct->pci_dev->dev, "BAR%d start: 0x%llx mapped %u of %u bytes\n",
		baridx, oct->mmio[baridx].start, mapped_len,
		oct->mmio[baridx].len);

	if (!oct->mmio[baridx].hw_addr) {
		dev_err(&oct->pci_dev->dev, "error ioremap for bar %d\n",
			baridx);
		goto err_release_region;
	}
	oct->mmio[baridx].done = 1;

	return 0;

err_release_region:
	pci_release_region(oct->pci_dev, baridx * 2);
	return 1;
}