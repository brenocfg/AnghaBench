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
typedef  int u32 ;
struct ata_port {int dummy; } ;
struct ata_device {int dma_mode; int devno; } ;

/* Variables and functions */
 scalar_t__ ATAC_CH0D0_DMA ; 
 int XFER_MW_DMA_0 ; 
 int XFER_UDMA_0 ; 
 int /*<<< orphan*/  rdmsr (scalar_t__,int,int) ; 
 int /*<<< orphan*/  wrmsr (scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cs5535_set_dmamode(struct ata_port *ap, struct ata_device *adev)
{
	static const u32 udma_timings[5] = {
		0x7F7436A1, 0x7F733481, 0x7F723261, 0x7F713161, 0x7F703061
	};
	static const u32 mwdma_timings[3] = {
		0x7F0FFFF3, 0x7F035352, 0x7F024241
	};
	u32 reg, dummy;
	int mode = adev->dma_mode;

	rdmsr(ATAC_CH0D0_DMA + 2 * adev->devno, reg, dummy);
	reg &= 0x80000000UL;
	if (mode >= XFER_UDMA_0)
		reg |= udma_timings[mode - XFER_UDMA_0];
	else
		reg |= mwdma_timings[mode - XFER_MW_DMA_0];
	wrmsr(ATAC_CH0D0_DMA + 2 * adev->devno, reg, 0);
}