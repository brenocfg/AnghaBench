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
struct stm32_mdma_device {scalar_t__ nr_requests; int /*<<< orphan*/  ddev; } ;
struct stm32_mdma_chan_config {scalar_t__ request; scalar_t__ priority_level; scalar_t__ transfer_config; scalar_t__ mask_addr; scalar_t__ mask_data; } ;
struct stm32_mdma_chan {struct stm32_mdma_chan_config chan_config; } ;
struct of_phandle_args {int args_count; scalar_t__* args; } ;
struct of_dma {struct stm32_mdma_device* of_dma_data; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 scalar_t__ STM32_MDMA_VERY_HIGH_PRIORITY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct dma_chan* dma_get_any_slave_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdma2dev (struct stm32_mdma_device*) ; 
 struct stm32_mdma_chan* to_stm32_mdma_chan (struct dma_chan*) ; 

__attribute__((used)) static struct dma_chan *stm32_mdma_of_xlate(struct of_phandle_args *dma_spec,
					    struct of_dma *ofdma)
{
	struct stm32_mdma_device *dmadev = ofdma->of_dma_data;
	struct stm32_mdma_chan *chan;
	struct dma_chan *c;
	struct stm32_mdma_chan_config config;

	if (dma_spec->args_count < 5) {
		dev_err(mdma2dev(dmadev), "Bad number of args\n");
		return NULL;
	}

	config.request = dma_spec->args[0];
	config.priority_level = dma_spec->args[1];
	config.transfer_config = dma_spec->args[2];
	config.mask_addr = dma_spec->args[3];
	config.mask_data = dma_spec->args[4];

	if (config.request >= dmadev->nr_requests) {
		dev_err(mdma2dev(dmadev), "Bad request line\n");
		return NULL;
	}

	if (config.priority_level > STM32_MDMA_VERY_HIGH_PRIORITY) {
		dev_err(mdma2dev(dmadev), "Priority level not supported\n");
		return NULL;
	}

	c = dma_get_any_slave_channel(&dmadev->ddev);
	if (!c) {
		dev_err(mdma2dev(dmadev), "No more channels available\n");
		return NULL;
	}

	chan = to_stm32_mdma_chan(c);
	chan->chan_config = config;

	return c;
}