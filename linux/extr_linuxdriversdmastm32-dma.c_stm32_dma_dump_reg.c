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
typedef  int /*<<< orphan*/  u32 ;
struct stm32_dma_device {int dummy; } ;
struct stm32_dma_chan {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  STM32_DMA_SCR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STM32_DMA_SFCR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STM32_DMA_SM0AR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STM32_DMA_SM1AR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STM32_DMA_SNDTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STM32_DMA_SPAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chan2dev (struct stm32_dma_chan*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct stm32_dma_device* stm32_dma_get_dev (struct stm32_dma_chan*) ; 
 int /*<<< orphan*/  stm32_dma_read (struct stm32_dma_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stm32_dma_dump_reg(struct stm32_dma_chan *chan)
{
	struct stm32_dma_device *dmadev = stm32_dma_get_dev(chan);
	u32 scr = stm32_dma_read(dmadev, STM32_DMA_SCR(chan->id));
	u32 ndtr = stm32_dma_read(dmadev, STM32_DMA_SNDTR(chan->id));
	u32 spar = stm32_dma_read(dmadev, STM32_DMA_SPAR(chan->id));
	u32 sm0ar = stm32_dma_read(dmadev, STM32_DMA_SM0AR(chan->id));
	u32 sm1ar = stm32_dma_read(dmadev, STM32_DMA_SM1AR(chan->id));
	u32 sfcr = stm32_dma_read(dmadev, STM32_DMA_SFCR(chan->id));

	dev_dbg(chan2dev(chan), "SCR:   0x%08x\n", scr);
	dev_dbg(chan2dev(chan), "NDTR:  0x%08x\n", ndtr);
	dev_dbg(chan2dev(chan), "SPAR:  0x%08x\n", spar);
	dev_dbg(chan2dev(chan), "SM0AR: 0x%08x\n", sm0ar);
	dev_dbg(chan2dev(chan), "SM1AR: 0x%08x\n", sm1ar);
	dev_dbg(chan2dev(chan), "SFCR:  0x%08x\n", sfcr);
}