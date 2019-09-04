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
struct sirfsoc_dma {TYPE_1__* channels; } ;
struct of_phandle_args {unsigned int* args; } ;
struct of_dma {struct sirfsoc_dma* of_dma_data; } ;
struct dma_chan {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 unsigned int SIRFSOC_DMA_CHANNELS ; 
 struct dma_chan* dma_get_slave_channel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dma_chan *of_dma_sirfsoc_xlate(struct of_phandle_args *dma_spec,
	struct of_dma *ofdma)
{
	struct sirfsoc_dma *sdma = ofdma->of_dma_data;
	unsigned int request = dma_spec->args[0];

	if (request >= SIRFSOC_DMA_CHANNELS)
		return NULL;

	return dma_get_slave_channel(&sdma->channels[request].chan);
}