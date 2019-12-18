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
struct comedi_isadma_desc {int n_desc; scalar_t__ chan2; scalar_t__ chan; struct comedi_isadma_desc* desc; int /*<<< orphan*/  hw_addr; scalar_t__ virt_addr; int /*<<< orphan*/  maxsize; int /*<<< orphan*/  dev; } ;
struct comedi_isadma {int n_desc; scalar_t__ chan2; scalar_t__ chan; struct comedi_isadma* desc; int /*<<< orphan*/  hw_addr; scalar_t__ virt_addr; int /*<<< orphan*/  maxsize; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_dma (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct comedi_isadma_desc*) ; 

void comedi_isadma_free(struct comedi_isadma *dma)
{
	struct comedi_isadma_desc *desc;
	int i;

	if (!dma)
		return;

	if (dma->desc) {
		for (i = 0; i < dma->n_desc; i++) {
			desc = &dma->desc[i];
			if (desc->virt_addr)
				dma_free_coherent(dma->dev, desc->maxsize,
						  desc->virt_addr,
						  desc->hw_addr);
		}
		kfree(dma->desc);
	}
	if (dma->chan2 && dma->chan2 != dma->chan)
		free_dma(dma->chan2);
	if (dma->chan)
		free_dma(dma->chan);
	kfree(dma);
}