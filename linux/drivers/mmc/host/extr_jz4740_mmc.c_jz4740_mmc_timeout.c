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
struct timer_list {int dummy; } ;
struct jz4740_mmc_host {TYPE_2__* req; int /*<<< orphan*/  waiting; } ;
struct TYPE_4__ {TYPE_1__* cmd; } ;
struct TYPE_3__ {int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  JZ_MMC_IRQ_END_CMD_RES ; 
 struct jz4740_mmc_host* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct jz4740_mmc_host* host ; 
 int /*<<< orphan*/  jz4740_mmc_request_done (struct jz4740_mmc_host*) ; 
 int /*<<< orphan*/  jz4740_mmc_set_irq_enabled (struct jz4740_mmc_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timeout_timer ; 

__attribute__((used)) static void jz4740_mmc_timeout(struct timer_list *t)
{
	struct jz4740_mmc_host *host = from_timer(host, t, timeout_timer);

	if (!test_and_clear_bit(0, &host->waiting))
		return;

	jz4740_mmc_set_irq_enabled(host, JZ_MMC_IRQ_END_CMD_RES, false);

	host->req->cmd->error = -ETIMEDOUT;
	jz4740_mmc_request_done(host);
}