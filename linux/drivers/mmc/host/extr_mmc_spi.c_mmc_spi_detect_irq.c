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
typedef  int /*<<< orphan*/  u16 ;
struct mmc_spi_host {TYPE_1__* pdata; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  detect_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_detect_change (void*,int /*<<< orphan*/ ) ; 
 struct mmc_spi_host* mmc_priv (void*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t
mmc_spi_detect_irq(int irq, void *mmc)
{
	struct mmc_spi_host *host = mmc_priv(mmc);
	u16 delay_msec = max(host->pdata->detect_delay, (u16)100);

	mmc_detect_change(mmc, msecs_to_jiffies(delay_msec));
	return IRQ_HANDLED;
}