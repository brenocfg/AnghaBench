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
typedef  int u16 ;
struct b43_dmaring {int nr_slots; TYPE_1__* dev; struct b43_dmadesc64* descbase; } ;
struct b43_dmadesc64 {void* address_high; void* address_low; void* control1; void* control0; } ;
struct b43_dmadesc_generic {struct b43_dmadesc64 dma64; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 int B43_DMA64_DCTL0_DTABLEEND ; 
 int B43_DMA64_DCTL0_FRAMEEND ; 
 int B43_DMA64_DCTL0_FRAMESTART ; 
 int B43_DMA64_DCTL0_IRQ ; 
 int B43_DMA64_DCTL1_ADDREXT_MASK ; 
 int B43_DMA64_DCTL1_ADDREXT_SHIFT ; 
 int B43_DMA64_DCTL1_BYTECNT ; 
 int /*<<< orphan*/  B43_DMA_ADDR_EXT ; 
 int /*<<< orphan*/  B43_DMA_ADDR_HIGH ; 
 int /*<<< orphan*/  B43_DMA_ADDR_LOW ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int b43_dma_address (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int) ; 

__attribute__((used)) static void op64_fill_descriptor(struct b43_dmaring *ring,
				 struct b43_dmadesc_generic *desc,
				 dma_addr_t dmaaddr, u16 bufsize,
				 int start, int end, int irq)
{
	struct b43_dmadesc64 *descbase = ring->descbase;
	int slot;
	u32 ctl0 = 0, ctl1 = 0;
	u32 addrlo, addrhi;
	u32 addrext;

	slot = (int)(&(desc->dma64) - descbase);
	B43_WARN_ON(!(slot >= 0 && slot < ring->nr_slots));

	addrlo = b43_dma_address(&ring->dev->dma, dmaaddr, B43_DMA_ADDR_LOW);
	addrhi = b43_dma_address(&ring->dev->dma, dmaaddr, B43_DMA_ADDR_HIGH);
	addrext = b43_dma_address(&ring->dev->dma, dmaaddr, B43_DMA_ADDR_EXT);

	if (slot == ring->nr_slots - 1)
		ctl0 |= B43_DMA64_DCTL0_DTABLEEND;
	if (start)
		ctl0 |= B43_DMA64_DCTL0_FRAMESTART;
	if (end)
		ctl0 |= B43_DMA64_DCTL0_FRAMEEND;
	if (irq)
		ctl0 |= B43_DMA64_DCTL0_IRQ;
	ctl1 |= bufsize & B43_DMA64_DCTL1_BYTECNT;
	ctl1 |= (addrext << B43_DMA64_DCTL1_ADDREXT_SHIFT)
	    & B43_DMA64_DCTL1_ADDREXT_MASK;

	desc->dma64.control0 = cpu_to_le32(ctl0);
	desc->dma64.control1 = cpu_to_le32(ctl1);
	desc->dma64.address_low = cpu_to_le32(addrlo);
	desc->dma64.address_high = cpu_to_le32(addrhi);
}