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
struct iavf_rx_buffer {int /*<<< orphan*/  pagecnt_bias; int /*<<< orphan*/  page_offset; int /*<<< orphan*/  dma; int /*<<< orphan*/  page; } ;
struct iavf_ring {size_t next_to_clean; int /*<<< orphan*/  dev; struct iavf_rx_buffer* rx_bi; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dma_sync_single_range_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetchw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct iavf_rx_buffer *iavf_get_rx_buffer(struct iavf_ring *rx_ring,
						 const unsigned int size)
{
	struct iavf_rx_buffer *rx_buffer;

	if (!size)
		return NULL;

	rx_buffer = &rx_ring->rx_bi[rx_ring->next_to_clean];
	prefetchw(rx_buffer->page);

	/* we are reusing so sync this buffer for CPU use */
	dma_sync_single_range_for_cpu(rx_ring->dev,
				      rx_buffer->dma,
				      rx_buffer->page_offset,
				      size,
				      DMA_FROM_DEVICE);

	/* We have pulled a buffer for use, so decrement pagecnt_bias */
	rx_buffer->pagecnt_bias--;

	return rx_buffer;
}