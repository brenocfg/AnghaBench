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
typedef  scalar_t__ u32 ;
struct pmcmsptwi_data {int /*<<< orphan*/  last_result; scalar_t__ iobase; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MSP_MAX_POLL ; 
 int /*<<< orphan*/  MSP_POLL_DELAY ; 
 scalar_t__ MSP_TWI_BUSY_REG_OFFSET ; 
 scalar_t__ MSP_TWI_INT_STS_REG_OFFSET ; 
 int /*<<< orphan*/  MSP_TWI_XFER_TIMEOUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__ pmcmsptwi_adapter ; 
 int /*<<< orphan*/  pmcmsptwi_get_result (scalar_t__) ; 
 scalar_t__ pmcmsptwi_readl (scalar_t__) ; 
 int /*<<< orphan*/  pmcmsptwi_writel (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pmcmsptwi_poll_complete(struct pmcmsptwi_data *data)
{
	int i;

	for (i = 0; i < MSP_MAX_POLL; i++) {
		u32 val = pmcmsptwi_readl(data->iobase +
						MSP_TWI_BUSY_REG_OFFSET);
		if (val == 0) {
			u32 reason = pmcmsptwi_readl(data->iobase +
						MSP_TWI_INT_STS_REG_OFFSET);
			pmcmsptwi_writel(reason, data->iobase +
						MSP_TWI_INT_STS_REG_OFFSET);
			data->last_result = pmcmsptwi_get_result(reason);
			return;
		}
		udelay(MSP_POLL_DELAY);
	}

	dev_dbg(&pmcmsptwi_adapter.dev, "Result: Poll timeout\n");
	data->last_result = MSP_TWI_XFER_TIMEOUT;
}