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
typedef  int /*<<< orphan*/  u32 ;
struct pmcmsptwi_data {int last_result; int /*<<< orphan*/  wait; scalar_t__ irq; scalar_t__ iobase; } ;
typedef  enum pmcmsptwi_xfer_result { ____Placeholder_pmcmsptwi_xfer_result } pmcmsptwi_xfer_result ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSP_IRQ_TIMEOUT ; 
 scalar_t__ MSP_TWI_CMD_REG_OFFSET ; 
 int MSP_TWI_XFER_TIMEOUT ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_1__ pmcmsptwi_adapter ; 
 int /*<<< orphan*/  pmcmsptwi_poll_complete (struct pmcmsptwi_data*) ; 
 int /*<<< orphan*/  pmcmsptwi_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum pmcmsptwi_xfer_result pmcmsptwi_do_xfer(
			u32 reg, struct pmcmsptwi_data *data)
{
	dev_dbg(&pmcmsptwi_adapter.dev, "Writing cmd reg 0x%08x\n", reg);
	pmcmsptwi_writel(reg, data->iobase + MSP_TWI_CMD_REG_OFFSET);
	if (data->irq) {
		unsigned long timeleft = wait_for_completion_timeout(
						&data->wait, MSP_IRQ_TIMEOUT);
		if (timeleft == 0) {
			dev_dbg(&pmcmsptwi_adapter.dev,
				"Result: IRQ timeout\n");
			complete(&data->wait);
			data->last_result = MSP_TWI_XFER_TIMEOUT;
		}
	} else
		pmcmsptwi_poll_complete(data);

	return data->last_result;
}