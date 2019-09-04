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
struct mdc_dma {int /*<<< orphan*/  periph_regs; } ;
struct mdc_chan {int periph; int /*<<< orphan*/  chan_nr; struct mdc_dma* mdma; } ;

/* Variables and functions */
 int /*<<< orphan*/  PISTACHIO_CR_PERIPH_DMA_ROUTE (int /*<<< orphan*/ ) ; 
 int PISTACHIO_CR_PERIPH_DMA_ROUTE_MASK ; 
 int PISTACHIO_CR_PERIPH_DMA_ROUTE_SHIFT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void pistachio_mdc_enable_chan(struct mdc_chan *mchan)
{
	struct mdc_dma *mdma = mchan->mdma;

	regmap_update_bits(mdma->periph_regs,
			   PISTACHIO_CR_PERIPH_DMA_ROUTE(mchan->chan_nr),
			   PISTACHIO_CR_PERIPH_DMA_ROUTE_MASK <<
			   PISTACHIO_CR_PERIPH_DMA_ROUTE_SHIFT(mchan->chan_nr),
			   mchan->periph <<
			   PISTACHIO_CR_PERIPH_DMA_ROUTE_SHIFT(mchan->chan_nr));
}