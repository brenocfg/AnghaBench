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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct orc_scb {int dummy; } ;
struct orc_host {int /*<<< orphan*/  scb_phys; int /*<<< orphan*/  scb_virt; int /*<<< orphan*/  escb_phys; int /*<<< orphan*/  escb_virt; } ;
struct orc_extended_scb {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  io_port; int /*<<< orphan*/  irq; scalar_t__ hostdata; } ;

/* Variables and functions */
 int ORC_MAXQUEUE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct Scsi_Host*) ; 
 struct Scsi_Host* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 

__attribute__((used)) static void inia100_remove_one(struct pci_dev *pdev)
{
	struct Scsi_Host *shost = pci_get_drvdata(pdev);
	struct orc_host *host = (struct orc_host *)shost->hostdata;

	scsi_remove_host(shost);

        free_irq(shost->irq, shost);
	dma_free_coherent(&pdev->dev,
			ORC_MAXQUEUE * sizeof(struct orc_extended_scb),
			host->escb_virt, host->escb_phys);
	dma_free_coherent(&pdev->dev,
			ORC_MAXQUEUE * sizeof(struct orc_scb),
			host->scb_virt, host->scb_phys);
        release_region(shost->io_port, 256);

	scsi_host_put(shost);
}