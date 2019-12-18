#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct b43_dmaring {scalar_t__ type; int frameoffset; int nr_slots; TYPE_1__* dev; int /*<<< orphan*/  dmabase; scalar_t__ tx; } ;
struct b43_dmadesc64 {int dummy; } ;
struct b43_dmadesc32 {int dummy; } ;
struct TYPE_4__ {int parity; } ;
struct TYPE_3__ {TYPE_2__ dma; } ;

/* Variables and functions */
 int B43_DMA32_RXADDREXT_MASK ; 
 int B43_DMA32_RXADDREXT_SHIFT ; 
 int /*<<< orphan*/  B43_DMA32_RXCTL ; 
 int B43_DMA32_RXENABLE ; 
 int B43_DMA32_RXFROFF_SHIFT ; 
 int /*<<< orphan*/  B43_DMA32_RXINDEX ; 
 int B43_DMA32_RXPARITYDISABLE ; 
 int /*<<< orphan*/  B43_DMA32_RXRING ; 
 int B43_DMA32_TXADDREXT_MASK ; 
 int B43_DMA32_TXADDREXT_SHIFT ; 
 int /*<<< orphan*/  B43_DMA32_TXCTL ; 
 int B43_DMA32_TXENABLE ; 
 int B43_DMA32_TXPARITYDISABLE ; 
 int /*<<< orphan*/  B43_DMA32_TXRING ; 
 int B43_DMA64_RXADDREXT_MASK ; 
 int B43_DMA64_RXADDREXT_SHIFT ; 
 int /*<<< orphan*/  B43_DMA64_RXCTL ; 
 int B43_DMA64_RXENABLE ; 
 int B43_DMA64_RXFROFF_SHIFT ; 
 int /*<<< orphan*/  B43_DMA64_RXINDEX ; 
 int B43_DMA64_RXPARITYDISABLE ; 
 int /*<<< orphan*/  B43_DMA64_RXRINGHI ; 
 int /*<<< orphan*/  B43_DMA64_RXRINGLO ; 
 int B43_DMA64_TXADDREXT_MASK ; 
 int B43_DMA64_TXADDREXT_SHIFT ; 
 int /*<<< orphan*/  B43_DMA64_TXCTL ; 
 int B43_DMA64_TXENABLE ; 
 int B43_DMA64_TXPARITYDISABLE ; 
 int /*<<< orphan*/  B43_DMA64_TXRINGHI ; 
 int /*<<< orphan*/  B43_DMA64_TXRINGLO ; 
 scalar_t__ B43_DMA_64BIT ; 
 int /*<<< orphan*/  B43_DMA_ADDR_EXT ; 
 int /*<<< orphan*/  B43_DMA_ADDR_HIGH ; 
 int /*<<< orphan*/  B43_DMA_ADDR_LOW ; 
 int alloc_initial_descbuffers (struct b43_dmaring*) ; 
 int b43_dma_address (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_dma_write (struct b43_dmaring*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dmacontroller_setup(struct b43_dmaring *ring)
{
	int err = 0;
	u32 value;
	u32 addrext;
	bool parity = ring->dev->dma.parity;
	u32 addrlo;
	u32 addrhi;

	if (ring->tx) {
		if (ring->type == B43_DMA_64BIT) {
			u64 ringbase = (u64) (ring->dmabase);
			addrext = b43_dma_address(&ring->dev->dma, ringbase, B43_DMA_ADDR_EXT);
			addrlo = b43_dma_address(&ring->dev->dma, ringbase, B43_DMA_ADDR_LOW);
			addrhi = b43_dma_address(&ring->dev->dma, ringbase, B43_DMA_ADDR_HIGH);

			value = B43_DMA64_TXENABLE;
			value |= (addrext << B43_DMA64_TXADDREXT_SHIFT)
			    & B43_DMA64_TXADDREXT_MASK;
			if (!parity)
				value |= B43_DMA64_TXPARITYDISABLE;
			b43_dma_write(ring, B43_DMA64_TXCTL, value);
			b43_dma_write(ring, B43_DMA64_TXRINGLO, addrlo);
			b43_dma_write(ring, B43_DMA64_TXRINGHI, addrhi);
		} else {
			u32 ringbase = (u32) (ring->dmabase);
			addrext = b43_dma_address(&ring->dev->dma, ringbase, B43_DMA_ADDR_EXT);
			addrlo = b43_dma_address(&ring->dev->dma, ringbase, B43_DMA_ADDR_LOW);

			value = B43_DMA32_TXENABLE;
			value |= (addrext << B43_DMA32_TXADDREXT_SHIFT)
			    & B43_DMA32_TXADDREXT_MASK;
			if (!parity)
				value |= B43_DMA32_TXPARITYDISABLE;
			b43_dma_write(ring, B43_DMA32_TXCTL, value);
			b43_dma_write(ring, B43_DMA32_TXRING, addrlo);
		}
	} else {
		err = alloc_initial_descbuffers(ring);
		if (err)
			goto out;
		if (ring->type == B43_DMA_64BIT) {
			u64 ringbase = (u64) (ring->dmabase);
			addrext = b43_dma_address(&ring->dev->dma, ringbase, B43_DMA_ADDR_EXT);
			addrlo = b43_dma_address(&ring->dev->dma, ringbase, B43_DMA_ADDR_LOW);
			addrhi = b43_dma_address(&ring->dev->dma, ringbase, B43_DMA_ADDR_HIGH);

			value = (ring->frameoffset << B43_DMA64_RXFROFF_SHIFT);
			value |= B43_DMA64_RXENABLE;
			value |= (addrext << B43_DMA64_RXADDREXT_SHIFT)
			    & B43_DMA64_RXADDREXT_MASK;
			if (!parity)
				value |= B43_DMA64_RXPARITYDISABLE;
			b43_dma_write(ring, B43_DMA64_RXCTL, value);
			b43_dma_write(ring, B43_DMA64_RXRINGLO, addrlo);
			b43_dma_write(ring, B43_DMA64_RXRINGHI, addrhi);
			b43_dma_write(ring, B43_DMA64_RXINDEX, ring->nr_slots *
				      sizeof(struct b43_dmadesc64));
		} else {
			u32 ringbase = (u32) (ring->dmabase);
			addrext = b43_dma_address(&ring->dev->dma, ringbase, B43_DMA_ADDR_EXT);
			addrlo = b43_dma_address(&ring->dev->dma, ringbase, B43_DMA_ADDR_LOW);

			value = (ring->frameoffset << B43_DMA32_RXFROFF_SHIFT);
			value |= B43_DMA32_RXENABLE;
			value |= (addrext << B43_DMA32_RXADDREXT_SHIFT)
			    & B43_DMA32_RXADDREXT_MASK;
			if (!parity)
				value |= B43_DMA32_RXPARITYDISABLE;
			b43_dma_write(ring, B43_DMA32_RXCTL, value);
			b43_dma_write(ring, B43_DMA32_RXRING, addrlo);
			b43_dma_write(ring, B43_DMA32_RXINDEX, ring->nr_slots *
				      sizeof(struct b43_dmadesc32));
		}
	}

out:
	return err;
}