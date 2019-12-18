#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u64 ;
struct TYPE_5__ {int /*<<< orphan*/  Opcode; } ;
struct TYPE_6__ {scalar_t__* raw8; TYPE_2__ hdr; } ;
struct ngene_command {int in_len; int out_len; TYPE_3__ cmd; } ;
struct ngene {int cmd_done; int BootFirmware; int PAFWInterfaceBuffer; scalar_t__* ngenetohost; int /*<<< orphan*/  prev_cmd; int /*<<< orphan*/  cmd_wq; int /*<<< orphan*/  cmd_lock; scalar_t__* CmdDoneByte; scalar_t__* FWInterfaceBuffer; int /*<<< orphan*/  icounts; TYPE_1__* pci_dev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FWLOAD_FINISH ; 
 int /*<<< orphan*/  CMD_FWLOAD_PREPARE ; 
 int /*<<< orphan*/  FORCE_INT ; 
 int /*<<< orphan*/  HOST_TO_NGENE ; 
 int HZ ; 
 int /*<<< orphan*/  NGENE_COMMAND ; 
 int /*<<< orphan*/  NGENE_COMMAND_HI ; 
 int /*<<< orphan*/  NGENE_EVENT ; 
 int /*<<< orphan*/  NGENE_EVENT_HI ; 
 int /*<<< orphan*/  NGENE_INT_COUNTS ; 
 int /*<<< orphan*/  NGENE_STATUS ; 
 int /*<<< orphan*/  NGENE_STATUS_HI ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_command_io (struct ngene*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  ngcpyto (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  ngreadl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngwritel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ngene_command_mutex(struct ngene *dev, struct ngene_command *com)
{
	struct device *pdev = &dev->pci_dev->dev;
	int ret;
	u8 *tmpCmdDoneByte;

	dev->cmd_done = 0;

	if (com->cmd.hdr.Opcode == CMD_FWLOAD_PREPARE) {
		dev->BootFirmware = 1;
		dev->icounts = ngreadl(NGENE_INT_COUNTS);
		ngwritel(0, NGENE_COMMAND);
		ngwritel(0, NGENE_COMMAND_HI);
		ngwritel(0, NGENE_STATUS);
		ngwritel(0, NGENE_STATUS_HI);
		ngwritel(0, NGENE_EVENT);
		ngwritel(0, NGENE_EVENT_HI);
	} else if (com->cmd.hdr.Opcode == CMD_FWLOAD_FINISH) {
		u64 fwio = dev->PAFWInterfaceBuffer;

		ngwritel(fwio & 0xffffffff, NGENE_COMMAND);
		ngwritel(fwio >> 32, NGENE_COMMAND_HI);
		ngwritel((fwio + 256) & 0xffffffff, NGENE_STATUS);
		ngwritel((fwio + 256) >> 32, NGENE_STATUS_HI);
		ngwritel((fwio + 512) & 0xffffffff, NGENE_EVENT);
		ngwritel((fwio + 512) >> 32, NGENE_EVENT_HI);
	}

	memcpy(dev->FWInterfaceBuffer, com->cmd.raw8, com->in_len + 2);

	if (dev->BootFirmware)
		ngcpyto(HOST_TO_NGENE, com->cmd.raw8, com->in_len + 2);

	spin_lock_irq(&dev->cmd_lock);
	tmpCmdDoneByte = dev->ngenetohost + com->out_len;
	if (!com->out_len)
		tmpCmdDoneByte++;
	*tmpCmdDoneByte = 0;
	dev->ngenetohost[0] = 0;
	dev->ngenetohost[1] = 0;
	dev->CmdDoneByte = tmpCmdDoneByte;
	spin_unlock_irq(&dev->cmd_lock);

	/* Notify 8051. */
	ngwritel(1, FORCE_INT);

	ret = wait_event_timeout(dev->cmd_wq, dev->cmd_done == 1, 2 * HZ);
	if (!ret) {
		/*ngwritel(0, FORCE_NMI);*/

		dev_err(pdev, "Command timeout cmd=%02x prev=%02x\n",
			com->cmd.hdr.Opcode, dev->prev_cmd);
		dump_command_io(dev);
		return -1;
	}
	if (com->cmd.hdr.Opcode == CMD_FWLOAD_FINISH)
		dev->BootFirmware = 0;

	dev->prev_cmd = com->cmd.hdr.Opcode;

	if (!com->out_len)
		return 0;

	memcpy(com->cmd.raw8, dev->ngenetohost, com->out_len);

	return 0;
}