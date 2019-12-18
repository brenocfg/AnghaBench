#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct usdhi6_host {int rate; int /*<<< orphan*/  mmc; struct mmc_request* mrq; } ;
struct mmc_request {TYPE_2__* data; TYPE_1__* cmd; } ;
struct TYPE_4__ {int timeout_ns; int timeout_clks; } ;
struct TYPE_3__ {int busy_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  USDHI6_SD_OPTION ; 
 int USDHI6_SD_OPTION_TIMEOUT_MASK ; 
 int USDHI6_SD_OPTION_TIMEOUT_SHIFT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*,unsigned long,int) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int order_base_2 (unsigned long) ; 
 int usdhi6_read (struct usdhi6_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usdhi6_write (struct usdhi6_host*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void usdhi6_timeout_set(struct usdhi6_host *host)
{
	struct mmc_request *mrq = host->mrq;
	u32 val;
	unsigned long ticks;

	if (!mrq->data)
		ticks = host->rate / 1000 * mrq->cmd->busy_timeout;
	else
		ticks = host->rate / 1000000 * (mrq->data->timeout_ns / 1000) +
			mrq->data->timeout_clks;

	if (!ticks || ticks > 1 << 27)
		/* Max timeout */
		val = 14;
	else if (ticks < 1 << 13)
		/* Min timeout */
		val = 0;
	else
		val = order_base_2(ticks) - 13;

	dev_dbg(mmc_dev(host->mmc), "Set %s timeout %lu ticks @ %lu Hz\n",
		mrq->data ? "data" : "cmd", ticks, host->rate);

	/* Timeout Counter mask: 0xf0 */
	usdhi6_write(host, USDHI6_SD_OPTION, (val << USDHI6_SD_OPTION_TIMEOUT_SHIFT) |
		     (usdhi6_read(host, USDHI6_SD_OPTION) & ~USDHI6_SD_OPTION_TIMEOUT_MASK));
}