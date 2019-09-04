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
typedef  int u32 ;
struct bgmac_dma_ring {int end; TYPE_1__* slots; struct bgmac_dma_desc* cpu_base; } ;
struct bgmac_dma_desc {void* ctl1; void* ctl0; void* addr_high; void* addr_low; } ;
struct bgmac {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_addr; } ;

/* Variables and functions */
 int BGMAC_DESC_CTL0_EOT ; 
 int BGMAC_DESC_CTL1_LEN ; 
 int BGMAC_RX_BUF_SIZE ; 
 int BGMAC_RX_RING_SLOTS ; 
 void* cpu_to_le32 (int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bgmac_dma_rx_setup_desc(struct bgmac *bgmac,
				    struct bgmac_dma_ring *ring, int desc_idx)
{
	struct bgmac_dma_desc *dma_desc = ring->cpu_base + desc_idx;
	u32 ctl0 = 0, ctl1 = 0;

	if (desc_idx == BGMAC_RX_RING_SLOTS - 1)
		ctl0 |= BGMAC_DESC_CTL0_EOT;
	ctl1 |= BGMAC_RX_BUF_SIZE & BGMAC_DESC_CTL1_LEN;
	/* Is there any BGMAC device that requires extension? */
	/* ctl1 |= (addrext << B43_DMA64_DCTL1_ADDREXT_SHIFT) &
	 * B43_DMA64_DCTL1_ADDREXT_MASK;
	 */

	dma_desc->addr_low = cpu_to_le32(lower_32_bits(ring->slots[desc_idx].dma_addr));
	dma_desc->addr_high = cpu_to_le32(upper_32_bits(ring->slots[desc_idx].dma_addr));
	dma_desc->ctl0 = cpu_to_le32(ctl0);
	dma_desc->ctl1 = cpu_to_le32(ctl1);

	ring->end = desc_idx;
}