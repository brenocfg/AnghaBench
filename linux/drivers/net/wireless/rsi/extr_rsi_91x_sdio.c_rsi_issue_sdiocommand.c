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
typedef  void* u32 ;
struct sdio_func {TYPE_1__* card; } ;
struct mmc_host {int dummy; } ;
struct mmc_command {void** resp; void* flags; void* arg; void* opcode; } ;
struct TYPE_2__ {struct mmc_host* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct mmc_command*,int /*<<< orphan*/ ,int) ; 
 int mmc_wait_for_cmd (struct mmc_host*,struct mmc_command*,int) ; 

__attribute__((used)) static int rsi_issue_sdiocommand(struct sdio_func *func,
				 u32 opcode,
				 u32 arg,
				 u32 flags,
				 u32 *resp)
{
	struct mmc_command cmd;
	struct mmc_host *host;
	int err;

	host = func->card->host;

	memset(&cmd, 0, sizeof(struct mmc_command));
	cmd.opcode = opcode;
	cmd.arg = arg;
	cmd.flags = flags;
	err = mmc_wait_for_cmd(host, &cmd, 3);

	if ((!err) && (resp))
		*resp = cmd.resp[0];

	return err;
}