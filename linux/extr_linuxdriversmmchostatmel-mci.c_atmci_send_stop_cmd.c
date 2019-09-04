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
struct mmc_data {int /*<<< orphan*/  stop; } ;
struct atmel_mci {int /*<<< orphan*/  stop_cmdr; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMCI_CMDRDY ; 
 int /*<<< orphan*/  ATMCI_IER ; 
 int /*<<< orphan*/  atmci_send_command (struct atmel_mci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmci_writel (struct atmel_mci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void atmci_send_stop_cmd(struct atmel_mci *host, struct mmc_data *data)
{
	dev_dbg(&host->pdev->dev, "send stop command\n");
	atmci_send_command(host, data->stop, host->stop_cmdr);
	atmci_writel(host, ATMCI_IER, ATMCI_CMDRDY);
}