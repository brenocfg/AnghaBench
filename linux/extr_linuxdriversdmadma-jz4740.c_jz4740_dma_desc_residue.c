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
struct jz4740_dmaengine_chan {unsigned int transfer_shift; int /*<<< orphan*/  id; } ;
struct jz4740_dma_dev {int dummy; } ;
struct jz4740_dma_desc {unsigned int num_sgs; TYPE_1__* sg; } ;
struct TYPE_2__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  JZ_REG_DMA_TRANSFER_COUNT (int /*<<< orphan*/ ) ; 
 struct jz4740_dma_dev* jz4740_dma_chan_get_dev (struct jz4740_dmaengine_chan*) ; 
 unsigned int jz4740_dma_read (struct jz4740_dma_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t jz4740_dma_desc_residue(struct jz4740_dmaengine_chan *chan,
	struct jz4740_dma_desc *desc, unsigned int next_sg)
{
	struct jz4740_dma_dev *dmadev = jz4740_dma_chan_get_dev(chan);
	unsigned int residue, count;
	unsigned int i;

	residue = 0;

	for (i = next_sg; i < desc->num_sgs; i++)
		residue += desc->sg[i].len;

	if (next_sg != 0) {
		count = jz4740_dma_read(dmadev,
			JZ_REG_DMA_TRANSFER_COUNT(chan->id));
		residue += count << chan->transfer_shift;
	}

	return residue;
}