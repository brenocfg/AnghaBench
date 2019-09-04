#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct ide_host {scalar_t__ host_priv; } ;
struct TYPE_4__ {int rqsize; int /*<<< orphan*/ * hwif_data; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;

/* Variables and functions */
 int /*<<< orphan*/  init_mmio_iops_siimage (TYPE_1__*) ; 
 struct ide_host* pci_get_drvdata (struct pci_dev*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_iops_siimage(ide_hwif_t *hwif)
{
	struct pci_dev *dev = to_pci_dev(hwif->dev);
	struct ide_host *host = pci_get_drvdata(dev);

	hwif->hwif_data = NULL;

	/* Pessimal until we finish probing */
	hwif->rqsize = 15;

	if (host->host_priv)
		init_mmio_iops_siimage(hwif);
}