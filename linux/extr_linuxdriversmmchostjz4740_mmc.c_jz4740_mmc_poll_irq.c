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
typedef  unsigned int uint32_t ;
struct jz4740_mmc_host {int /*<<< orphan*/  timeout_timer; int /*<<< orphan*/  waiting; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ jiffies ; 
 unsigned int jz4740_mmc_read_irq_reg (struct jz4740_mmc_host*) ; 
 int /*<<< orphan*/  jz4740_mmc_set_irq_enabled (struct jz4740_mmc_host*,unsigned int,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int jz4740_mmc_poll_irq(struct jz4740_mmc_host *host,
	unsigned int irq)
{
	unsigned int timeout = 0x800;
	uint32_t status;

	do {
		status = jz4740_mmc_read_irq_reg(host);
	} while (!(status & irq) && --timeout);

	if (timeout == 0) {
		set_bit(0, &host->waiting);
		mod_timer(&host->timeout_timer, jiffies + 5*HZ);
		jz4740_mmc_set_irq_enabled(host, irq, true);
		return true;
	}

	return false;
}