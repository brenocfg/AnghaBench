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
struct i40e_rx_buffer {int /*<<< orphan*/  dma; } ;
struct i40e_ring {size_t next_to_clean; int /*<<< orphan*/  dev; struct i40e_rx_buffer* rx_bi; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  dma_sync_single_range_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct i40e_rx_buffer *i40e_get_rx_buffer_zc(struct i40e_ring *rx_ring,
						    const unsigned int size)
{
	struct i40e_rx_buffer *bi;

	bi = &rx_ring->rx_bi[rx_ring->next_to_clean];

	/* we are reusing so sync this buffer for CPU use */
	dma_sync_single_range_for_cpu(rx_ring->dev,
				      bi->dma, 0,
				      size,
				      DMA_BIDIRECTIONAL);

	return bi;
}