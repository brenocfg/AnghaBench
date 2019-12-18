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
struct mantis_pci {int /*<<< orphan*/ * risc_cpu; scalar_t__ risc_dma; int /*<<< orphan*/  pdev; int /*<<< orphan*/ * buf_cpu; scalar_t__ buf_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANTIS_BUF_SIZE ; 
 int /*<<< orphan*/  MANTIS_ERROR ; 
 int /*<<< orphan*/  MANTIS_RISC_SIZE ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

int mantis_dma_exit(struct mantis_pci *mantis)
{
	if (mantis->buf_cpu) {
		dprintk(MANTIS_ERROR, 1,
			"DMA=0x%lx cpu=0x%p size=%d",
			(unsigned long) mantis->buf_dma,
			 mantis->buf_cpu,
			 MANTIS_BUF_SIZE);

		pci_free_consistent(mantis->pdev, MANTIS_BUF_SIZE,
				    mantis->buf_cpu, mantis->buf_dma);

		mantis->buf_cpu = NULL;
	}
	if (mantis->risc_cpu) {
		dprintk(MANTIS_ERROR, 1,
			"RISC=0x%lx cpu=0x%p size=%lx",
			(unsigned long) mantis->risc_dma,
			mantis->risc_cpu,
			MANTIS_RISC_SIZE);

		pci_free_consistent(mantis->pdev, MANTIS_RISC_SIZE,
				    mantis->risc_cpu, mantis->risc_dma);

		mantis->risc_cpu = NULL;
	}

	return 0;
}