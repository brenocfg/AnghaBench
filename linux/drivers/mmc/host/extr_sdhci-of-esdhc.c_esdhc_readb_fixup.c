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
typedef  int u32 ;
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 int SDHCI_CTRL_DMA_MASK ; 
 int SDHCI_HOST_CONTROL ; 

__attribute__((used)) static u8 esdhc_readb_fixup(struct sdhci_host *host,
				     int spec_reg, u32 value)
{
	u8 ret;
	u8 dma_bits;
	int shift = (spec_reg & 0x3) * 8;

	ret = (value >> shift) & 0xff;

	/*
	 * "DMA select" locates at offset 0x28 in SD specification, but on
	 * P5020 or P3041, it locates at 0x29.
	 */
	if (spec_reg == SDHCI_HOST_CONTROL) {
		/* DMA select is 22,23 bits in Protocol Control Register */
		dma_bits = (value >> 5) & SDHCI_CTRL_DMA_MASK;
		/* fixup the result */
		ret &= ~SDHCI_CTRL_DMA_MASK;
		ret |= dma_bits;
	}
	return ret;
}