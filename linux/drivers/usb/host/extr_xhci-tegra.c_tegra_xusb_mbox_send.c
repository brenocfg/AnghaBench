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
typedef  int u32 ;
struct tegra_xusb_mbox_msg {scalar_t__ cmd; } ;
struct tegra_xusb {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int ETIMEDOUT ; 
 scalar_t__ MBOX_CMD_ACK ; 
 scalar_t__ MBOX_CMD_NAK ; 
 int MBOX_DEST_FALC ; 
 int MBOX_INT_EN ; 
 int MBOX_OWNER_NONE ; 
 int MBOX_OWNER_SW ; 
 int /*<<< orphan*/  XUSB_CFG_ARU_MBOX_CMD ; 
 int /*<<< orphan*/  XUSB_CFG_ARU_MBOX_DATA_IN ; 
 int /*<<< orphan*/  XUSB_CFG_ARU_MBOX_OWNER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int fpci_readl (struct tegra_xusb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpci_writel (struct tegra_xusb*,int,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int tegra_xusb_mbox_pack (struct tegra_xusb_mbox_msg const*) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int tegra_xusb_mbox_send(struct tegra_xusb *tegra,
				const struct tegra_xusb_mbox_msg *msg)
{
	bool wait_for_idle = false;
	u32 value;

	/*
	 * Acquire the mailbox. The firmware still owns the mailbox for
	 * ACK/NAK messages.
	 */
	if (!(msg->cmd == MBOX_CMD_ACK || msg->cmd == MBOX_CMD_NAK)) {
		value = fpci_readl(tegra, XUSB_CFG_ARU_MBOX_OWNER);
		if (value != MBOX_OWNER_NONE) {
			dev_err(tegra->dev, "mailbox is busy\n");
			return -EBUSY;
		}

		fpci_writel(tegra, MBOX_OWNER_SW, XUSB_CFG_ARU_MBOX_OWNER);

		value = fpci_readl(tegra, XUSB_CFG_ARU_MBOX_OWNER);
		if (value != MBOX_OWNER_SW) {
			dev_err(tegra->dev, "failed to acquire mailbox\n");
			return -EBUSY;
		}

		wait_for_idle = true;
	}

	value = tegra_xusb_mbox_pack(msg);
	fpci_writel(tegra, value, XUSB_CFG_ARU_MBOX_DATA_IN);

	value = fpci_readl(tegra, XUSB_CFG_ARU_MBOX_CMD);
	value |= MBOX_INT_EN | MBOX_DEST_FALC;
	fpci_writel(tegra, value, XUSB_CFG_ARU_MBOX_CMD);

	if (wait_for_idle) {
		unsigned long timeout = jiffies + msecs_to_jiffies(250);

		while (time_before(jiffies, timeout)) {
			value = fpci_readl(tegra, XUSB_CFG_ARU_MBOX_OWNER);
			if (value == MBOX_OWNER_NONE)
				break;

			usleep_range(10, 20);
		}

		if (time_after(jiffies, timeout))
			value = fpci_readl(tegra, XUSB_CFG_ARU_MBOX_OWNER);

		if (value != MBOX_OWNER_NONE)
			return -ETIMEDOUT;
	}

	return 0;
}