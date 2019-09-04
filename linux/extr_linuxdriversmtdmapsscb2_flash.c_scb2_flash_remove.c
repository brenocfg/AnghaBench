#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCB2_ADDR ; 
 int /*<<< orphan*/  SCB2_WINDOW ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  mtd_device_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  mtd_lock (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  region_fail ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * scb2_ioaddr ; 
 TYPE_1__* scb2_mtd ; 

__attribute__((used)) static void scb2_flash_remove(struct pci_dev *dev)
{
	if (!scb2_mtd)
		return;

	/* disable flash writes */
	mtd_lock(scb2_mtd, 0, scb2_mtd->size);

	mtd_device_unregister(scb2_mtd);
	map_destroy(scb2_mtd);

	iounmap(scb2_ioaddr);
	scb2_ioaddr = NULL;

	if (!region_fail)
		release_mem_region(SCB2_ADDR, SCB2_WINDOW);
}