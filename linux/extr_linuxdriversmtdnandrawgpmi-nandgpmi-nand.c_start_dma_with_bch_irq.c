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
struct gpmi_nand_data {int /*<<< orphan*/  dev; struct completion bch_done; } ;
struct dma_async_tx_descriptor {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpmi_dump_info (struct gpmi_nand_data*) ; 
 int /*<<< orphan*/  init_completion (struct completion*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  start_dma_without_bch_irq (struct gpmi_nand_data*,struct dma_async_tx_descriptor*) ; 
 unsigned long wait_for_completion_timeout (struct completion*,int /*<<< orphan*/ ) ; 

int start_dma_with_bch_irq(struct gpmi_nand_data *this,
			struct dma_async_tx_descriptor *desc)
{
	struct completion *bch_c = &this->bch_done;
	unsigned long timeout;

	/* Prepare to receive an interrupt from the BCH block. */
	init_completion(bch_c);

	/* start the DMA */
	start_dma_without_bch_irq(this, desc);

	/* Wait for the interrupt from the BCH block. */
	timeout = wait_for_completion_timeout(bch_c, msecs_to_jiffies(1000));
	if (!timeout) {
		dev_err(this->dev, "BCH timeout\n");
		gpmi_dump_info(this);
		return -ETIMEDOUT;
	}
	return 0;
}