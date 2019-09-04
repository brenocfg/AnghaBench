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
typedef  scalar_t__ u32 ;
struct moxart_host {int /*<<< orphan*/  mmc; scalar_t__ base; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ MAX_RETRIES ; 
 scalar_t__ REG_CLEAR ; 
 scalar_t__ REG_STATUS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int moxart_wait_for_status(struct moxart_host *host,
				  u32 mask, u32 *status)
{
	int ret = -ETIMEDOUT;
	u32 i;

	for (i = 0; i < MAX_RETRIES; i++) {
		*status = readl(host->base + REG_STATUS);
		if (!(*status & mask)) {
			udelay(5);
			continue;
		}
		writel(*status & mask, host->base + REG_CLEAR);
		ret = 0;
		break;
	}

	if (ret)
		dev_err(mmc_dev(host->mmc), "timed out waiting for status\n");

	return ret;
}