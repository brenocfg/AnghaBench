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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  sense_interrupt_reg; } ;
struct ipr_ioa_cfg {TYPE_1__ regs; } ;

/* Variables and functions */
 int EIO ; 
 int volatile IPR_PCII_IO_DEBUG_ACKNOWLEDGE ; 
 int MAX_UDELAY_MS ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ipr_wait_iodbg_ack(struct ipr_ioa_cfg *ioa_cfg, int max_delay)
{
	volatile u32 pcii_reg;
	int delay = 1;

	/* Read interrupt reg until IOA signals IO Debug Acknowledge */
	while (delay < max_delay) {
		pcii_reg = readl(ioa_cfg->regs.sense_interrupt_reg);

		if (pcii_reg & IPR_PCII_IO_DEBUG_ACKNOWLEDGE)
			return 0;

		/* udelay cannot be used if delay is more than a few milliseconds */
		if ((delay / 1000) > MAX_UDELAY_MS)
			mdelay(delay / 1000);
		else
			udelay(delay);

		delay += delay;
	}
	return -EIO;
}