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
struct omap_sg {int /*<<< orphan*/  fn; int /*<<< orphan*/  en; int /*<<< orphan*/  fi; int /*<<< orphan*/  ei; int /*<<< orphan*/  addr; } ;
struct omap_desc {scalar_t__ dir; struct omap_sg* sg; } ;
struct omap_chan {int sgidx; } ;

/* Variables and functions */
 unsigned int CDEI ; 
 unsigned int CDFI ; 
 unsigned int CDSA ; 
 unsigned int CEN ; 
 unsigned int CFN ; 
 unsigned int CSEI ; 
 unsigned int CSFI ; 
 unsigned int CSSA ; 
 scalar_t__ DMA_DEV_TO_MEM ; 
 scalar_t__ DMA_MEM_TO_MEM ; 
 int /*<<< orphan*/  omap_dma_chan_write (struct omap_chan*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_dma_start (struct omap_chan*,struct omap_desc*) ; 

__attribute__((used)) static void omap_dma_start_sg(struct omap_chan *c, struct omap_desc *d)
{
	struct omap_sg *sg = d->sg + c->sgidx;
	unsigned cxsa, cxei, cxfi;

	if (d->dir == DMA_DEV_TO_MEM || d->dir == DMA_MEM_TO_MEM) {
		cxsa = CDSA;
		cxei = CDEI;
		cxfi = CDFI;
	} else {
		cxsa = CSSA;
		cxei = CSEI;
		cxfi = CSFI;
	}

	omap_dma_chan_write(c, cxsa, sg->addr);
	omap_dma_chan_write(c, cxei, sg->ei);
	omap_dma_chan_write(c, cxfi, sg->fi);
	omap_dma_chan_write(c, CEN, sg->en);
	omap_dma_chan_write(c, CFN, sg->fn);

	omap_dma_start(c, d);
	c->sgidx++;
}