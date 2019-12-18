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
struct usbnet {int /*<<< orphan*/  phy_mutex; int /*<<< orphan*/  net; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  __u16 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  AX_CMD_STATMNGSTS_REG ; 
 int /*<<< orphan*/  AX_CMD_WRITE_MII_REG ; 
 int AX_HOST_EN ; 
 int ENODEV ; 
 int asix_read_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asix_set_hw_mii (struct usbnet*,int /*<<< orphan*/ ) ; 
 int asix_set_sw_mii (struct usbnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asix_write_cmd (struct usbnet*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int,int,int) ; 
 struct usbnet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void asix_mdio_write(struct net_device *netdev, int phy_id, int loc, int val)
{
	struct usbnet *dev = netdev_priv(netdev);
	__le16 res = cpu_to_le16(val);
	u8 smsr;
	int i = 0;
	int ret;

	netdev_dbg(dev->net, "asix_mdio_write() phy_id=0x%02x, loc=0x%02x, val=0x%04x\n",
			phy_id, loc, val);

	mutex_lock(&dev->phy_mutex);
	do {
		ret = asix_set_sw_mii(dev, 0);
		if (ret == -ENODEV)
			break;
		usleep_range(1000, 1100);
		ret = asix_read_cmd(dev, AX_CMD_STATMNGSTS_REG,
				    0, 0, 1, &smsr, 0);
	} while (!(smsr & AX_HOST_EN) && (i++ < 30) && (ret != -ENODEV));
	if (ret == -ENODEV) {
		mutex_unlock(&dev->phy_mutex);
		return;
	}

	asix_write_cmd(dev, AX_CMD_WRITE_MII_REG, phy_id,
		       (__u16)loc, 2, &res, 0);
	asix_set_hw_mii(dev, 0);
	mutex_unlock(&dev->phy_mutex);
}