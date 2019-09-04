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
struct sh_mmcif_host {int /*<<< orphan*/  addr; } ;
struct mmc_command {int /*<<< orphan*/ * resp; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMCIF_CE_RESP_CMD12 ; 
 int /*<<< orphan*/  sh_mmcif_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh_mmcif_get_cmd12response(struct sh_mmcif_host *host,
						struct mmc_command *cmd)
{
	cmd->resp[0] = sh_mmcif_readl(host->addr, MMCIF_CE_RESP_CMD12);
}