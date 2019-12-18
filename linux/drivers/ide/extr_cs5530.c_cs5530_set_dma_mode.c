#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ide_hwif_t ;
struct TYPE_3__ {int dma_mode; int dn; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 unsigned long CS5530_BASEREG (int /*<<< orphan*/ *) ; 
#define  XFER_MW_DMA_0 133 
#define  XFER_MW_DMA_1 132 
#define  XFER_MW_DMA_2 131 
#define  XFER_UDMA_0 130 
#define  XFER_UDMA_1 129 
#define  XFER_UDMA_2 128 
 unsigned int inl (unsigned long) ; 
 int /*<<< orphan*/  outl (unsigned int,unsigned long) ; 

__attribute__((used)) static void cs5530_set_dma_mode(ide_hwif_t *hwif, ide_drive_t *drive)
{
	unsigned long basereg;
	unsigned int reg, timings = 0;

	switch (drive->dma_mode) {
		case XFER_UDMA_0:	timings = 0x00921250; break;
		case XFER_UDMA_1:	timings = 0x00911140; break;
		case XFER_UDMA_2:	timings = 0x00911030; break;
		case XFER_MW_DMA_0:	timings = 0x00077771; break;
		case XFER_MW_DMA_1:	timings = 0x00012121; break;
		case XFER_MW_DMA_2:	timings = 0x00002020; break;
	}
	basereg = CS5530_BASEREG(hwif);
	reg = inl(basereg + 4);			/* get drive0 config register */
	timings |= reg & 0x80000000;		/* preserve PIO format bit */
	if ((drive-> dn & 1) == 0) {		/* are we configuring drive0? */
		outl(timings, basereg + 4);	/* write drive0 config register */
	} else {
		if (timings & 0x00100000)
			reg |=  0x00100000;	/* enable UDMA timings for both drives */
		else
			reg &= ~0x00100000;	/* disable UDMA timings for both drives */
		outl(reg, basereg + 4);		/* write drive0 config register */
		outl(timings, basereg + 12);	/* write drive1 config register */
	}
}