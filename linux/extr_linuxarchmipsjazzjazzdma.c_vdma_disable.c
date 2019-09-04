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
 scalar_t__ JAZZ_DUMMY_DEVICE ; 
 scalar_t__ JAZZ_R4030_CHNL_ADDR ; 
 scalar_t__ JAZZ_R4030_CHNL_COUNT ; 
 scalar_t__ JAZZ_R4030_CHNL_ENABLE ; 
 scalar_t__ JAZZ_R4030_CHNL_MODE ; 
 int R4030_CHNL_ENABLE ; 
 int /*<<< orphan*/  printk (char*,int,...) ; 
 int r4030_read_reg32 (scalar_t__) ; 
 int /*<<< orphan*/  r4030_write_reg32 (scalar_t__,int) ; 
 scalar_t__ vdma_debug ; 

void vdma_disable(int channel)
{
	if (vdma_debug) {
		int status =
		    r4030_read_reg32(JAZZ_R4030_CHNL_ENABLE +
				     (channel << 5));

		printk("vdma_disable: channel %d\n", channel);
		printk("VDMA: channel %d status: %04x (%s) mode: "
		       "%02x addr: %06x count: %06x\n",
		       channel, status,
		       ((status & 0x600) ? "ERROR" : "OK"),
		       (unsigned) r4030_read_reg32(JAZZ_R4030_CHNL_MODE +
						   (channel << 5)),
		       (unsigned) r4030_read_reg32(JAZZ_R4030_CHNL_ADDR +
						   (channel << 5)),
		       (unsigned) r4030_read_reg32(JAZZ_R4030_CHNL_COUNT +
						   (channel << 5)));
	}

	r4030_write_reg32(JAZZ_R4030_CHNL_ENABLE + (channel << 5),
			  r4030_read_reg32(JAZZ_R4030_CHNL_ENABLE +
					   (channel << 5)) &
			  ~R4030_CHNL_ENABLE);

	/*
	 * After disabling a DMA channel a remote bus register should be
	 * read to ensure that the current DMA acknowledge cycle is completed.
	 */
	*((volatile unsigned int *) JAZZ_DUMMY_DEVICE);
}