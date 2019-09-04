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
struct completion {int dummy; } ;
struct gpmi_nand_data {int /*<<< orphan*/  dev; struct completion dma_done; } ;
struct dma_async_tx_descriptor {struct gpmi_nand_data* callback_param; int /*<<< orphan*/  callback; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_irq_callback ; 
 int /*<<< orphan*/  dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  get_dma_chan (struct gpmi_nand_data*) ; 
 int /*<<< orphan*/  gpmi_dump_info (struct gpmi_nand_data*) ; 
 int /*<<< orphan*/  init_completion (struct completion*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 unsigned long wait_for_completion_timeout (struct completion*,int /*<<< orphan*/ ) ; 

int start_dma_without_bch_irq(struct gpmi_nand_data *this,
				struct dma_async_tx_descriptor *desc)
{
	struct completion *dma_c = &this->dma_done;
	unsigned long timeout;

	init_completion(dma_c);

	desc->callback		= dma_irq_callback;
	desc->callback_param	= this;
	dmaengine_submit(desc);
	dma_async_issue_pending(get_dma_chan(this));

	/* Wait for the interrupt from the DMA block. */
	timeout = wait_for_completion_timeout(dma_c, msecs_to_jiffies(1000));
	if (!timeout) {
		dev_err(this->dev, "DMA timeout, last DMA\n");
		gpmi_dump_info(this);
		return -ETIMEDOUT;
	}
	return 0;
}