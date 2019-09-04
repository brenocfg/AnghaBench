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
struct TYPE_2__ {int dma_scr; } ;
struct stm32_dma_chan {int /*<<< orphan*/  threshold; TYPE_1__ chan_reg; } ;
struct stm32_dma_cfg {int stream_config; int /*<<< orphan*/  features; int /*<<< orphan*/  request_line; } ;

/* Variables and functions */
 int STM32_DMA_SCR_CFG_MASK ; 
 int STM32_DMA_SCR_REQ (int /*<<< orphan*/ ) ; 
 int STM32_DMA_SCR_TCIE ; 
 int STM32_DMA_SCR_TEIE ; 
 int /*<<< orphan*/  STM32_DMA_THRESHOLD_FTR_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_dma_clear_reg (TYPE_1__*) ; 

__attribute__((used)) static void stm32_dma_set_config(struct stm32_dma_chan *chan,
				 struct stm32_dma_cfg *cfg)
{
	stm32_dma_clear_reg(&chan->chan_reg);

	chan->chan_reg.dma_scr = cfg->stream_config & STM32_DMA_SCR_CFG_MASK;
	chan->chan_reg.dma_scr |= STM32_DMA_SCR_REQ(cfg->request_line);

	/* Enable Interrupts  */
	chan->chan_reg.dma_scr |= STM32_DMA_SCR_TEIE | STM32_DMA_SCR_TCIE;

	chan->threshold = STM32_DMA_THRESHOLD_FTR_GET(cfg->features);
}