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
struct atmel_aes_dma {int /*<<< orphan*/  chan; } ;
struct atmel_aes_dev {struct atmel_aes_dma dst; struct atmel_aes_dma src; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;

/* Variables and functions */
#define  DMA_DEV_TO_MEM 129 
#define  DMA_MEM_TO_DEV 128 
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atmel_aes_dma_transfer_stop(struct atmel_aes_dev *dd,
					enum dma_transfer_direction dir)
{
	struct atmel_aes_dma *dma;

	switch (dir) {
	case DMA_MEM_TO_DEV:
		dma = &dd->src;
		break;

	case DMA_DEV_TO_MEM:
		dma = &dd->dst;
		break;

	default:
		return;
	}

	dmaengine_terminate_all(dma->chan);
}