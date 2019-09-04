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
struct brcmnand_host {struct brcmnand_controller* ctrl; } ;
struct brcmnand_controller {int dma_pending; int /*<<< orphan*/  dev; int /*<<< orphan*/  dma_done; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  FLASH_DMA_CTRL ; 
 int /*<<< orphan*/  FLASH_DMA_ERROR_STATUS ; 
 int /*<<< orphan*/  FLASH_DMA_FIRST_DESC ; 
 int /*<<< orphan*/  FLASH_DMA_FIRST_DESC_EXT ; 
 int /*<<< orphan*/  FLASH_DMA_STATUS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flash_dma_readl (struct brcmnand_controller*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flash_dma_writel (struct brcmnand_controller*,int /*<<< orphan*/ ,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 unsigned long msecs_to_jiffies (int) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 
 scalar_t__ wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void brcmnand_dma_run(struct brcmnand_host *host, dma_addr_t desc)
{
	struct brcmnand_controller *ctrl = host->ctrl;
	unsigned long timeo = msecs_to_jiffies(100);

	flash_dma_writel(ctrl, FLASH_DMA_FIRST_DESC, lower_32_bits(desc));
	(void)flash_dma_readl(ctrl, FLASH_DMA_FIRST_DESC);
	flash_dma_writel(ctrl, FLASH_DMA_FIRST_DESC_EXT, upper_32_bits(desc));
	(void)flash_dma_readl(ctrl, FLASH_DMA_FIRST_DESC_EXT);

	/* Start FLASH_DMA engine */
	ctrl->dma_pending = true;
	mb(); /* flush previous writes */
	flash_dma_writel(ctrl, FLASH_DMA_CTRL, 0x03); /* wake | run */

	if (wait_for_completion_timeout(&ctrl->dma_done, timeo) <= 0) {
		dev_err(ctrl->dev,
				"timeout waiting for DMA; status %#x, error status %#x\n",
				flash_dma_readl(ctrl, FLASH_DMA_STATUS),
				flash_dma_readl(ctrl, FLASH_DMA_ERROR_STATUS));
	}
	ctrl->dma_pending = false;
	flash_dma_writel(ctrl, FLASH_DMA_CTRL, 0); /* force stop */
}