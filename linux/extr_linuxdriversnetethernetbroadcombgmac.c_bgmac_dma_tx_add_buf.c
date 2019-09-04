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
struct bgmac_slot_info {int /*<<< orphan*/  dma_addr; } ;
struct bgmac_dma_ring {struct bgmac_dma_desc* cpu_base; struct bgmac_slot_info* slots; } ;
struct bgmac_dma_desc {void* ctl1; void* ctl0; void* addr_high; void* addr_low; } ;
struct bgmac {int dummy; } ;

/* Variables and functions */
 int BGMAC_DESC_CTL0_EOT ; 
 int BGMAC_DESC_CTL1_LEN ; 
 int BGMAC_TX_RING_SLOTS ; 
 void* cpu_to_le32 (int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bgmac_dma_tx_add_buf(struct bgmac *bgmac, struct bgmac_dma_ring *ring,
		     int i, int len, u32 ctl0)
{
	struct bgmac_slot_info *slot;
	struct bgmac_dma_desc *dma_desc;
	u32 ctl1;

	if (i == BGMAC_TX_RING_SLOTS - 1)
		ctl0 |= BGMAC_DESC_CTL0_EOT;

	ctl1 = len & BGMAC_DESC_CTL1_LEN;

	slot = &ring->slots[i];
	dma_desc = &ring->cpu_base[i];
	dma_desc->addr_low = cpu_to_le32(lower_32_bits(slot->dma_addr));
	dma_desc->addr_high = cpu_to_le32(upper_32_bits(slot->dma_addr));
	dma_desc->ctl0 = cpu_to_le32(ctl0);
	dma_desc->ctl1 = cpu_to_le32(ctl1);
}