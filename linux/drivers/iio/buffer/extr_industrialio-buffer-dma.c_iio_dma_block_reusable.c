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
struct iio_dma_buffer_block {int state; } ;

/* Variables and functions */
#define  IIO_BLOCK_STATE_DEQUEUED 130 
#define  IIO_BLOCK_STATE_DONE 129 
#define  IIO_BLOCK_STATE_QUEUED 128 

__attribute__((used)) static bool iio_dma_block_reusable(struct iio_dma_buffer_block *block)
{
	/*
	 * If the core owns the block it can be re-used. This should be the
	 * default case when enabling the buffer, unless the DMA controller does
	 * not support abort and has not given back the block yet.
	 */
	switch (block->state) {
	case IIO_BLOCK_STATE_DEQUEUED:
	case IIO_BLOCK_STATE_QUEUED:
	case IIO_BLOCK_STATE_DONE:
		return true;
	default:
		return false;
	}
}