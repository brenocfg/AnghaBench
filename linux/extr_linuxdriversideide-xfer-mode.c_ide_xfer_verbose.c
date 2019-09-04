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
typedef  int u8 ;

/* Variables and functions */
 int XFER_MW_DMA_0 ; 
 int XFER_MW_DMA_4 ; 
 int XFER_PIO_0 ; 
 int XFER_PIO_6 ; 
 int XFER_PIO_SLOW ; 
 int XFER_SW_DMA_0 ; 
 int XFER_SW_DMA_2 ; 
 int XFER_UDMA_0 ; 
 int XFER_UDMA_7 ; 
 char** mwdma_str ; 
 char** pio_str ; 
 char** swdma_str ; 
 char** udma_str ; 

const char *ide_xfer_verbose(u8 mode)
{
	const char *s;
	u8 i = mode & 0xf;

	if (mode >= XFER_UDMA_0 && mode <= XFER_UDMA_7)
		s = udma_str[i];
	else if (mode >= XFER_MW_DMA_0 && mode <= XFER_MW_DMA_4)
		s = mwdma_str[i];
	else if (mode >= XFER_SW_DMA_0 && mode <= XFER_SW_DMA_2)
		s = swdma_str[i];
	else if (mode >= XFER_PIO_0 && mode <= XFER_PIO_6)
		s = pio_str[i & 0x7];
	else if (mode == XFER_PIO_SLOW)
		s = "PIO SLOW";
	else
		s = "XFER ERROR";

	return s;
}