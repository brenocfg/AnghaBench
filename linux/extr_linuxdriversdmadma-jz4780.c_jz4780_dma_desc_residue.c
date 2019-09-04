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
struct jz4780_dma_dev {int dummy; } ;
struct jz4780_dma_desc {unsigned int count; TYPE_1__* desc; } ;
struct jz4780_dma_chan {unsigned int transfer_shift; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {unsigned int dtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  JZ_DMA_REG_DTC (int /*<<< orphan*/ ) ; 
 struct jz4780_dma_dev* jz4780_dma_chan_parent (struct jz4780_dma_chan*) ; 
 unsigned int jz4780_dma_readl (struct jz4780_dma_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t jz4780_dma_desc_residue(struct jz4780_dma_chan *jzchan,
	struct jz4780_dma_desc *desc, unsigned int next_sg)
{
	struct jz4780_dma_dev *jzdma = jz4780_dma_chan_parent(jzchan);
	unsigned int residue, count;
	unsigned int i;

	residue = 0;

	for (i = next_sg; i < desc->count; i++)
		residue += desc->desc[i].dtc << jzchan->transfer_shift;

	if (next_sg != 0) {
		count = jz4780_dma_readl(jzdma,
					 JZ_DMA_REG_DTC(jzchan->id));
		residue += count << jzchan->transfer_shift;
	}

	return residue;
}