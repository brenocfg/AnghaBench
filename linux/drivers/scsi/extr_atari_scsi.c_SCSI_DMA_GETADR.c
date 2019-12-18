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
struct TYPE_2__ {unsigned long dma_lo; int dma_md; int dma_hi; } ;

/* Variables and functions */
 int /*<<< orphan*/  MFPDELAY () ; 
 TYPE_1__ st_dma ; 

__attribute__((used)) static inline unsigned long SCSI_DMA_GETADR(void)
{
	unsigned long adr;
	adr = st_dma.dma_lo;
	MFPDELAY();
	adr |= (st_dma.dma_md & 0xff) << 8;
	MFPDELAY();
	adr |= (st_dma.dma_hi & 0xff) << 16;
	MFPDELAY();
	return adr;
}