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
struct mantis_pci {int dummy; } ;

/* Variables and functions */
 int MANTIS_DCAP_EN ; 
 int /*<<< orphan*/  MANTIS_DEBUG ; 
 int /*<<< orphan*/  MANTIS_DMA_CTL ; 
 int MANTIS_FIFO_EN ; 
 int /*<<< orphan*/  MANTIS_GPIF_ADDR ; 
 int MANTIS_GPIF_HIFRDWRN ; 
 int MANTIS_INT_RISCEN ; 
 int MANTIS_INT_RISCI ; 
 int /*<<< orphan*/  MANTIS_INT_STAT ; 
 int MANTIS_RISC_EN ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  mantis_mask_ints (struct mantis_pci*,int) ; 
 int mmread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmwrite (int,int /*<<< orphan*/ ) ; 

void mantis_dma_stop(struct mantis_pci *mantis)
{
	dprintk(MANTIS_DEBUG, 1, "Mantis Stop DMA engine");

	mmwrite((mmread(MANTIS_GPIF_ADDR) & (~(MANTIS_GPIF_HIFRDWRN))), MANTIS_GPIF_ADDR);

	mmwrite((mmread(MANTIS_DMA_CTL) & ~(MANTIS_FIFO_EN |
					    MANTIS_DCAP_EN |
					    MANTIS_RISC_EN)), MANTIS_DMA_CTL);

	mmwrite(mmread(MANTIS_INT_STAT), MANTIS_INT_STAT);

	mantis_mask_ints(mantis, MANTIS_INT_RISCI | MANTIS_INT_RISCEN);
}