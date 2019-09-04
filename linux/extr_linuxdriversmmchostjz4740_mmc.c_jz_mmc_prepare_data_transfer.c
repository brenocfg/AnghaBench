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
struct mmc_data {int flags; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; } ;
struct mmc_command {struct mmc_data* data; } ;
struct jz4740_mmc_host {int /*<<< orphan*/  miter; TYPE_1__* req; } ;
struct TYPE_2__ {struct mmc_command* cmd; } ;

/* Variables and functions */
 int MMC_DATA_READ ; 
 int SG_MITER_FROM_SG ; 
 int SG_MITER_TO_SG ; 
 int /*<<< orphan*/  sg_miter_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void jz_mmc_prepare_data_transfer(struct jz4740_mmc_host *host)
{
	struct mmc_command *cmd = host->req->cmd;
	struct mmc_data *data = cmd->data;
	int direction;

	if (data->flags & MMC_DATA_READ)
		direction = SG_MITER_TO_SG;
	else
		direction = SG_MITER_FROM_SG;

	sg_miter_start(&host->miter, data->sg, data->sg_len, direction);
}