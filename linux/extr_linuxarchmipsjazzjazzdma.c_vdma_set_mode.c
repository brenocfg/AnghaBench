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

/* Variables and functions */
#define  DMA_MODE_READ 133 
#define  DMA_MODE_WRITE 132 
#define  JAZZ_AUDIOL_DMA 131 
#define  JAZZ_AUDIOR_DMA 130 
#define  JAZZ_FLOPPY_DMA 129 
 int /*<<< orphan*/  JAZZ_R4030_CHNL_ENABLE ; 
 int /*<<< orphan*/  JAZZ_R4030_CHNL_MODE ; 
#define  JAZZ_SCSI_DMA 128 
 int R4030_CHNL_WRITE ; 
 int R4030_MODE_ATIME_120 ; 
 int R4030_MODE_ATIME_80 ; 
 int R4030_MODE_INTR_EN ; 
 int R4030_MODE_WIDTH_16 ; 
 int R4030_MODE_WIDTH_8 ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int r4030_read_reg32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r4030_write_reg32 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ vdma_debug ; 

void vdma_set_mode(int channel, int mode)
{
	if (vdma_debug)
		printk("vdma_set_mode: channel %d, mode 0x%x\n", channel,
		       mode);

	switch (channel) {
	case JAZZ_SCSI_DMA:	/* scsi */
		r4030_write_reg32(JAZZ_R4030_CHNL_MODE + (channel << 5),
/*			  R4030_MODE_FAST | */
/*			  R4030_MODE_BURST | */
				  R4030_MODE_INTR_EN |
				  R4030_MODE_WIDTH_16 |
				  R4030_MODE_ATIME_80);
		break;

	case JAZZ_FLOPPY_DMA:	/* floppy */
		r4030_write_reg32(JAZZ_R4030_CHNL_MODE + (channel << 5),
/*			  R4030_MODE_FAST | */
/*			  R4030_MODE_BURST | */
				  R4030_MODE_INTR_EN |
				  R4030_MODE_WIDTH_8 |
				  R4030_MODE_ATIME_120);
		break;

	case JAZZ_AUDIOL_DMA:
	case JAZZ_AUDIOR_DMA:
		printk("VDMA: Audio DMA not supported yet.\n");
		break;

	default:
		printk
		    ("VDMA: vdma_set_mode() called with unsupported channel %d!\n",
		     channel);
	}

	switch (mode) {
	case DMA_MODE_READ:
		r4030_write_reg32(JAZZ_R4030_CHNL_ENABLE + (channel << 5),
				  r4030_read_reg32(JAZZ_R4030_CHNL_ENABLE +
						   (channel << 5)) &
				  ~R4030_CHNL_WRITE);
		break;

	case DMA_MODE_WRITE:
		r4030_write_reg32(JAZZ_R4030_CHNL_ENABLE + (channel << 5),
				  r4030_read_reg32(JAZZ_R4030_CHNL_ENABLE +
						   (channel << 5)) |
				  R4030_CHNL_WRITE);
		break;

	default:
		printk
		    ("VDMA: vdma_set_mode() called with unknown dma mode 0x%x\n",
		     mode);
	}
}