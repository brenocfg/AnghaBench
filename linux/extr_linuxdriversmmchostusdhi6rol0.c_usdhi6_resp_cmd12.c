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
struct usdhi6_host {TYPE_1__* mrq; } ;
struct mmc_command {int /*<<< orphan*/ * resp; } ;
struct TYPE_2__ {struct mmc_command* stop; } ;

/* Variables and functions */
 int /*<<< orphan*/  USDHI6_SD_RSP10 ; 
 int /*<<< orphan*/  usdhi6_read (struct usdhi6_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usdhi6_resp_cmd12(struct usdhi6_host *host)
{
	struct mmc_command *cmd = host->mrq->stop;
	cmd->resp[0] = usdhi6_read(host, USDHI6_SD_RSP10);
}