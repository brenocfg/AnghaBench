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
typedef  int u8 ;
struct usbnet {int /*<<< orphan*/  net; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  AX_CMD_READ_PHY_ID ; 
 int asix_read_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 

int asix_read_phy_addr(struct usbnet *dev, int internal)
{
	int offset = (internal ? 1 : 0);
	u8 buf[2];
	int ret = asix_read_cmd(dev, AX_CMD_READ_PHY_ID, 0, 0, 2, buf, 0);

	netdev_dbg(dev->net, "asix_get_phy_addr()\n");

	if (ret < 0) {
		netdev_err(dev->net, "Error reading PHYID register: %02x\n", ret);
		goto out;
	}
	netdev_dbg(dev->net, "asix_get_phy_addr() returning 0x%04x\n",
		   *((__le16 *)buf));
	ret = buf[offset];

out:
	return ret;
}