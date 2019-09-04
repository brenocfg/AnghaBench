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
struct stm32_dma_device {int /*<<< orphan*/  clk; } ;
struct stm32_dma_chan {int config_init; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  chan2dev (struct stm32_dma_chan*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int stm32_dma_disable_chan (struct stm32_dma_chan*) ; 
 struct stm32_dma_device* stm32_dma_get_dev (struct stm32_dma_chan*) ; 
 struct stm32_dma_chan* to_stm32_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static int stm32_dma_alloc_chan_resources(struct dma_chan *c)
{
	struct stm32_dma_chan *chan = to_stm32_dma_chan(c);
	struct stm32_dma_device *dmadev = stm32_dma_get_dev(chan);
	int ret;

	chan->config_init = false;
	ret = clk_prepare_enable(dmadev->clk);
	if (ret < 0) {
		dev_err(chan2dev(chan), "clk_prepare_enable failed: %d\n", ret);
		return ret;
	}

	ret = stm32_dma_disable_chan(chan);
	if (ret < 0)
		clk_disable_unprepare(dmadev->clk);

	return ret;
}