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
struct stm32_adc {unsigned int rx_buf_sz; unsigned int bufi; TYPE_1__* dma_chan; } ;
struct dma_tx_state {unsigned int residue; } ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;
struct TYPE_2__ {int /*<<< orphan*/  cookie; } ;

/* Variables and functions */
 int DMA_IN_PROGRESS ; 
 int dmaengine_tx_status (TYPE_1__*,int /*<<< orphan*/ ,struct dma_tx_state*) ; 

__attribute__((used)) static unsigned int stm32_adc_dma_residue(struct stm32_adc *adc)
{
	struct dma_tx_state state;
	enum dma_status status;

	status = dmaengine_tx_status(adc->dma_chan,
				     adc->dma_chan->cookie,
				     &state);
	if (status == DMA_IN_PROGRESS) {
		/* Residue is size in bytes from end of buffer */
		unsigned int i = adc->rx_buf_sz - state.residue;
		unsigned int size;

		/* Return available bytes */
		if (i >= adc->bufi)
			size = i - adc->bufi;
		else
			size = adc->rx_buf_sz + i - adc->bufi;

		return size;
	}

	return 0;
}