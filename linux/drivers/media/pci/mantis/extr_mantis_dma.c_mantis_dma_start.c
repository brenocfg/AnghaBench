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
struct mantis_pci {int risc_dma; scalar_t__ busy_block; scalar_t__ last_block; } ;

/* Variables and functions */
 int MANTIS_DCAP_EN ; 
 int /*<<< orphan*/  MANTIS_DEBUG ; 
 int /*<<< orphan*/  MANTIS_DMA_CTL ; 
 int MANTIS_FIFO_EN ; 
 int /*<<< orphan*/  MANTIS_GPIF_ADDR ; 
 int MANTIS_GPIF_HIFRDWRN ; 
 int /*<<< orphan*/  MANTIS_INT_RISCI ; 
 int MANTIS_RISC_EN ; 
 int /*<<< orphan*/  MANTIS_RISC_START ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  mantis_risc_program (struct mantis_pci*) ; 
 int /*<<< orphan*/  mantis_unmask_ints (struct mantis_pci*,int /*<<< orphan*/ ) ; 
 int mmread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmwrite (int,int /*<<< orphan*/ ) ; 

void mantis_dma_start(struct mantis_pci *mantis)
{
	dprintk(MANTIS_DEBUG, 1, "Mantis Start DMA engine");

	mantis_risc_program(mantis);
	mmwrite(mantis->risc_dma, MANTIS_RISC_START);
	mmwrite(mmread(MANTIS_GPIF_ADDR) | MANTIS_GPIF_HIFRDWRN, MANTIS_GPIF_ADDR);

	mmwrite(0, MANTIS_DMA_CTL);
	mantis->last_block = mantis->busy_block = 0;

	mantis_unmask_ints(mantis, MANTIS_INT_RISCI);

	mmwrite(MANTIS_FIFO_EN | MANTIS_DCAP_EN
			       | MANTIS_RISC_EN, MANTIS_DMA_CTL);

}