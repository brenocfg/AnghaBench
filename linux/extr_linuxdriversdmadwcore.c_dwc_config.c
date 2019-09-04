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
typedef  void* u32 ;
struct dma_slave_config {int src_maxburst; int dst_maxburst; int /*<<< orphan*/  direction; } ;
struct dw_dma_chan {int /*<<< orphan*/  direction; struct dma_slave_config dma_sconfig; } ;
struct dw_dma {TYPE_1__* pdata; } ;
struct dma_chan {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {scalar_t__ is_idma32; } ;

/* Variables and functions */
 int EINVAL ; 
 void* fls (int) ; 
 int /*<<< orphan*/  is_slave_direction (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct dma_slave_config*,struct dma_slave_config*,int) ; 
 struct dw_dma* to_dw_dma (int /*<<< orphan*/ ) ; 
 struct dw_dma_chan* to_dw_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static int dwc_config(struct dma_chan *chan, struct dma_slave_config *sconfig)
{
	struct dw_dma_chan *dwc = to_dw_dma_chan(chan);
	struct dma_slave_config *sc = &dwc->dma_sconfig;
	struct dw_dma *dw = to_dw_dma(chan->device);
	/*
	 * Fix sconfig's burst size according to dw_dmac. We need to convert
	 * them as:
	 * 1 -> 0, 4 -> 1, 8 -> 2, 16 -> 3.
	 *
	 * NOTE: burst size 2 is not supported by DesignWare controller.
	 *       iDMA 32-bit supports it.
	 */
	u32 s = dw->pdata->is_idma32 ? 1 : 2;

	/* Check if chan will be configured for slave transfers */
	if (!is_slave_direction(sconfig->direction))
		return -EINVAL;

	memcpy(&dwc->dma_sconfig, sconfig, sizeof(*sconfig));
	dwc->direction = sconfig->direction;

	sc->src_maxburst = sc->src_maxburst > 1 ? fls(sc->src_maxburst) - s : 0;
	sc->dst_maxburst = sc->dst_maxburst > 1 ? fls(sc->dst_maxburst) - s : 0;

	return 0;
}