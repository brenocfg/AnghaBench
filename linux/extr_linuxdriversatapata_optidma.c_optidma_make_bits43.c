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
struct ata_device {int dma_mode; size_t pio_mode; } ;

/* Variables and functions */
 int XFER_MW_DMA_0 ; 
 size_t XFER_PIO_0 ; 
 int /*<<< orphan*/  ata_dev_enabled (struct ata_device*) ; 

__attribute__((used)) static u8 optidma_make_bits43(struct ata_device *adev)
{
	static const u8 bits43[5] = {
		0, 0, 0, 1, 2
	};
	if (!ata_dev_enabled(adev))
		return 0;
	if (adev->dma_mode)
		return adev->dma_mode - XFER_MW_DMA_0;
	return bits43[adev->pio_mode - XFER_PIO_0];
}