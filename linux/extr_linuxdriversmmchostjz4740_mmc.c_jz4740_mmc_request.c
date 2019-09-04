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
struct mmc_request {int /*<<< orphan*/  cmd; } ;
struct mmc_host {int dummy; } ;
struct jz4740_mmc_host {int /*<<< orphan*/  timeout_timer; int /*<<< orphan*/  waiting; int /*<<< orphan*/  state; struct mmc_request* req; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  JZ4740_MMC_STATE_READ_RESPONSE ; 
 int /*<<< orphan*/  JZ_MMC_IRQ_END_CMD_RES ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  jz4740_mmc_send_command (struct jz4740_mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jz4740_mmc_set_irq_enabled (struct jz4740_mmc_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jz4740_mmc_write_irq_reg (struct jz4740_mmc_host*,int /*<<< orphan*/ ) ; 
 struct jz4740_mmc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void jz4740_mmc_request(struct mmc_host *mmc, struct mmc_request *req)
{
	struct jz4740_mmc_host *host = mmc_priv(mmc);

	host->req = req;

	jz4740_mmc_write_irq_reg(host, ~0);
	jz4740_mmc_set_irq_enabled(host, JZ_MMC_IRQ_END_CMD_RES, true);

	host->state = JZ4740_MMC_STATE_READ_RESPONSE;
	set_bit(0, &host->waiting);
	mod_timer(&host->timeout_timer, jiffies + 5*HZ);
	jz4740_mmc_send_command(host, req->cmd);
}