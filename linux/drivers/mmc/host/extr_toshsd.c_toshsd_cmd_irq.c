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
typedef  int u8 ;
typedef  int u16 ;
struct toshsd_host {scalar_t__ data; TYPE_1__* pdev; scalar_t__ ioaddr; struct mmc_command* cmd; } ;
struct mmc_command {int flags; int /*<<< orphan*/  error; int /*<<< orphan*/  opcode; scalar_t__ resp; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MMC_RSP_136 ; 
 int MMC_RSP_PRESENT ; 
 scalar_t__ SD_RESPONSE0 ; 
 scalar_t__ SD_RESPONSE1 ; 
 scalar_t__ SD_RESPONSE2 ; 
 scalar_t__ SD_RESPONSE3 ; 
 scalar_t__ SD_RESPONSE4 ; 
 scalar_t__ SD_RESPONSE5 ; 
 scalar_t__ SD_RESPONSE6 ; 
 scalar_t__ SD_RESPONSE7 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int ioread16 (scalar_t__) ; 
 int /*<<< orphan*/  toshsd_finish_request (struct toshsd_host*) ; 

__attribute__((used)) static void toshsd_cmd_irq(struct toshsd_host *host)
{
	struct mmc_command *cmd = host->cmd;
	u8 *buf;
	u16 data;

	if (!host->cmd) {
		dev_warn(&host->pdev->dev, "Spurious CMD irq\n");
		return;
	}
	buf = (u8 *)cmd->resp;
	host->cmd = NULL;

	if (cmd->flags & MMC_RSP_PRESENT && cmd->flags & MMC_RSP_136) {
		/* R2 */
		buf[12] = 0xff;
		data = ioread16(host->ioaddr + SD_RESPONSE0);
		buf[13] = data & 0xff;
		buf[14] = data >> 8;
		data = ioread16(host->ioaddr + SD_RESPONSE1);
		buf[15] = data & 0xff;
		buf[8] = data >> 8;
		data = ioread16(host->ioaddr + SD_RESPONSE2);
		buf[9] = data & 0xff;
		buf[10] = data >> 8;
		data = ioread16(host->ioaddr + SD_RESPONSE3);
		buf[11] = data & 0xff;
		buf[4] = data >> 8;
		data = ioread16(host->ioaddr + SD_RESPONSE4);
		buf[5] = data & 0xff;
		buf[6] = data >> 8;
		data = ioread16(host->ioaddr + SD_RESPONSE5);
		buf[7] = data & 0xff;
		buf[0] = data >> 8;
		data = ioread16(host->ioaddr + SD_RESPONSE6);
		buf[1] = data & 0xff;
		buf[2] = data >> 8;
		data = ioread16(host->ioaddr + SD_RESPONSE7);
		buf[3] = data & 0xff;
	} else if (cmd->flags & MMC_RSP_PRESENT) {
		/* R1, R1B, R3, R6, R7 */
		data = ioread16(host->ioaddr + SD_RESPONSE0);
		buf[0] = data & 0xff;
		buf[1] = data >> 8;
		data = ioread16(host->ioaddr + SD_RESPONSE1);
		buf[2] = data & 0xff;
		buf[3] = data >> 8;
	}

	dev_dbg(&host->pdev->dev, "Command IRQ complete %d %d %x\n",
		cmd->opcode, cmd->error, cmd->flags);

	/* If there is data to handle we will
	 * finish the request in the mmc_data_end_irq handler.*/
	if (host->data)
		return;

	toshsd_finish_request(host);
}