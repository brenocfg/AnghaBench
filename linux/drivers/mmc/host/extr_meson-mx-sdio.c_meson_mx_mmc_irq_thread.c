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
struct mmc_command {TYPE_1__* data; } ;
struct meson_mx_mmc_host {int /*<<< orphan*/  mmc; int /*<<< orphan*/  cmd_timeout; struct mmc_command* cmd; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int bytes_xfered; int blksz; int blocks; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mmc_command* meson_mx_mmc_get_next_cmd (struct mmc_command*) ; 
 int /*<<< orphan*/  meson_mx_mmc_request_done (struct meson_mx_mmc_host*) ; 
 int /*<<< orphan*/  meson_mx_mmc_start_cmd (int /*<<< orphan*/ ,struct mmc_command*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_get_dma_dir (TYPE_1__*) ; 

__attribute__((used)) static irqreturn_t meson_mx_mmc_irq_thread(int irq, void *irq_data)
{
	struct meson_mx_mmc_host *host = (void *) irq_data;
	struct mmc_command *cmd = host->cmd, *next_cmd;

	if (WARN_ON(!cmd))
		return IRQ_HANDLED;

	del_timer_sync(&host->cmd_timeout);

	if (cmd->data) {
		dma_unmap_sg(mmc_dev(host->mmc), cmd->data->sg,
				cmd->data->sg_len,
				mmc_get_dma_dir(cmd->data));

		cmd->data->bytes_xfered = cmd->data->blksz * cmd->data->blocks;
	}

	next_cmd = meson_mx_mmc_get_next_cmd(cmd);
	if (next_cmd)
		meson_mx_mmc_start_cmd(host->mmc, next_cmd);
	else
		meson_mx_mmc_request_done(host);

	return IRQ_HANDLED;
}