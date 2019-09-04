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
struct pl330_dmac {unsigned int num_peripherals; TYPE_1__* peripherals; } ;
struct of_phandle_args {int args_count; unsigned int* args; } ;
struct of_dma {struct pl330_dmac* of_dma_data; } ;
struct dma_chan {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 struct dma_chan* dma_get_slave_channel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dma_chan *of_dma_pl330_xlate(struct of_phandle_args *dma_spec,
						struct of_dma *ofdma)
{
	int count = dma_spec->args_count;
	struct pl330_dmac *pl330 = ofdma->of_dma_data;
	unsigned int chan_id;

	if (!pl330)
		return NULL;

	if (count != 1)
		return NULL;

	chan_id = dma_spec->args[0];
	if (chan_id >= pl330->num_peripherals)
		return NULL;

	return dma_get_slave_channel(&pl330->peripherals[chan_id].chan);
}