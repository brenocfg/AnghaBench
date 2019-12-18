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
struct tbnet_ring {scalar_t__ prod; scalar_t__ cons; TYPE_2__* ring; struct tbnet_frame* frames; } ;
struct TYPE_3__ {scalar_t__ buffer_phy; } ;
struct tbnet_frame {int /*<<< orphan*/ * page; TYPE_1__ frame; } ;
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_4__ {scalar_t__ is_tx; } ;

/* Variables and functions */
 int DMA_FROM_DEVICE ; 
 int DMA_TO_DEVICE ; 
 size_t TBNET_FRAME_SIZE ; 
 unsigned int TBNET_RING_SIZE ; 
 unsigned int TBNET_RX_PAGE_ORDER ; 
 size_t TBNET_RX_PAGE_SIZE ; 
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,scalar_t__,size_t,int) ; 
 struct device* tb_ring_dma_device (TYPE_2__*) ; 

__attribute__((used)) static void tbnet_free_buffers(struct tbnet_ring *ring)
{
	unsigned int i;

	for (i = 0; i < TBNET_RING_SIZE; i++) {
		struct device *dma_dev = tb_ring_dma_device(ring->ring);
		struct tbnet_frame *tf = &ring->frames[i];
		enum dma_data_direction dir;
		unsigned int order;
		size_t size;

		if (!tf->page)
			continue;

		if (ring->ring->is_tx) {
			dir = DMA_TO_DEVICE;
			order = 0;
			size = TBNET_FRAME_SIZE;
		} else {
			dir = DMA_FROM_DEVICE;
			order = TBNET_RX_PAGE_ORDER;
			size = TBNET_RX_PAGE_SIZE;
		}

		if (tf->frame.buffer_phy)
			dma_unmap_page(dma_dev, tf->frame.buffer_phy, size,
				       dir);

		__free_pages(tf->page, order);
		tf->page = NULL;
	}

	ring->cons = 0;
	ring->prod = 0;
}