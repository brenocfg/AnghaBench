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
struct scsi_qla_host {int /*<<< orphan*/  response_dma; int /*<<< orphan*/  response_ring; TYPE_1__* pdev; int /*<<< orphan*/  request_dma; int /*<<< orphan*/  request_ring; int /*<<< orphan*/  mmpbase; } ;
struct response {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct Scsi_Host {int /*<<< orphan*/  io_port; scalar_t__ hostdata; } ;
typedef  int /*<<< orphan*/  request_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int REQUEST_ENTRY_CNT ; 
 int RESPONSE_ENTRY_CNT ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct scsi_qla_host*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct Scsi_Host* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  qla1280_disable_intrs (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 

__attribute__((used)) static void
qla1280_remove_one(struct pci_dev *pdev)
{
	struct Scsi_Host *host = pci_get_drvdata(pdev);
	struct scsi_qla_host *ha = (struct scsi_qla_host *)host->hostdata;

	scsi_remove_host(host);

	qla1280_disable_intrs(ha);

	free_irq(pdev->irq, ha);

#if MEMORY_MAPPED_IO
	iounmap(ha->mmpbase);
#else
	release_region(host->io_port, 0xff);
#endif

	dma_free_coherent(&ha->pdev->dev,
			((REQUEST_ENTRY_CNT + 1) * (sizeof(request_t))),
			ha->request_ring, ha->request_dma);
	dma_free_coherent(&ha->pdev->dev,
			((RESPONSE_ENTRY_CNT + 1) * (sizeof(struct response))),
			ha->response_ring, ha->response_dma);

	pci_disable_device(pdev);

	scsi_host_put(host);
}