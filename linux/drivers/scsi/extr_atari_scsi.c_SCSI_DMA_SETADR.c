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
struct TYPE_2__ {unsigned char dma_lo; unsigned char dma_md; unsigned char dma_hi; } ;

/* Variables and functions */
 int /*<<< orphan*/  MFPDELAY () ; 
 TYPE_1__ st_dma ; 

__attribute__((used)) static inline void SCSI_DMA_SETADR(unsigned long adr)
{
	st_dma.dma_lo = (unsigned char)adr;
	MFPDELAY();
	adr >>= 8;
	st_dma.dma_md = (unsigned char)adr;
	MFPDELAY();
	adr >>= 8;
	st_dma.dma_hi = (unsigned char)adr;
	MFPDELAY();
}