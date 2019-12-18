#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct Scsi_Host {scalar_t__ n_io_port; scalar_t__ io_port; scalar_t__ irq; scalar_t__ hostdata; } ;
struct TYPE_5__ {scalar_t__ MmioAddress; int /*<<< orphan*/  sg_paddr; scalar_t__ sg_list; TYPE_1__* Pci; int /*<<< orphan*/  auto_paddr; scalar_t__ autoparam; } ;
typedef  TYPE_2__ nsp32_hw_data ;
typedef  int /*<<< orphan*/  nsp32_autoparam ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int NSP32_SG_TABLE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  release_region (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int nsp32_release(struct Scsi_Host *host)
{
	nsp32_hw_data *data = (nsp32_hw_data *)host->hostdata;

	if (data->autoparam) {
		dma_free_coherent(&data->Pci->dev, sizeof(nsp32_autoparam),
				    data->autoparam, data->auto_paddr);
	}

	if (data->sg_list) {
		dma_free_coherent(&data->Pci->dev, NSP32_SG_TABLE_SIZE,
				    data->sg_list, data->sg_paddr);
	}

	if (host->irq) {
		free_irq(host->irq, data);
	}

	if (host->io_port && host->n_io_port) {
		release_region(host->io_port, host->n_io_port);
	}

	if (data->MmioAddress) {
		iounmap(data->MmioAddress);
	}

	return 0;
}