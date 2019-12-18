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
typedef  int /*<<< orphan*/  u64 ;
struct b43_dmaring {int type; TYPE_2__* dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dma_dev; } ;

/* Variables and functions */
#define  B43_DMA_30BIT 130 
#define  B43_DMA_32BIT 129 
#define  B43_DMA_64BIT 128 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmap_descbuffer (struct b43_dmaring*,int /*<<< orphan*/ ,size_t,int) ; 

__attribute__((used)) static bool b43_dma_mapping_error(struct b43_dmaring *ring,
				  dma_addr_t addr,
				  size_t buffersize, bool dma_to_device)
{
	if (unlikely(dma_mapping_error(ring->dev->dev->dma_dev, addr)))
		return true;

	switch (ring->type) {
	case B43_DMA_30BIT:
		if ((u64)addr + buffersize > (1ULL << 30))
			goto address_error;
		break;
	case B43_DMA_32BIT:
		if ((u64)addr + buffersize > (1ULL << 32))
			goto address_error;
		break;
	case B43_DMA_64BIT:
		/* Currently we can't have addresses beyond
		 * 64bit in the kernel. */
		break;
	}

	/* The address is OK. */
	return false;

address_error:
	/* We can't support this address. Unmap it again. */
	unmap_descbuffer(ring, addr, buffersize, dma_to_device);

	return true;
}