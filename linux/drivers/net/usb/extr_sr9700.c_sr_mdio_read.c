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
struct usbnet {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int __le16 ;

/* Variables and functions */
 int BMSR_LSTATUS ; 
 int MII_BMSR ; 
 int NSR_LINKST ; 
 int /*<<< orphan*/  SR_NSR ; 
 int le16_to_cpu (int) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,...) ; 
 struct usbnet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sr_read_reg (struct usbnet*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sr_share_read_word (struct usbnet*,int,int,int*) ; 

__attribute__((used)) static int sr_mdio_read(struct net_device *netdev, int phy_id, int loc)
{
	struct usbnet *dev = netdev_priv(netdev);
	__le16 res;
	int rc = 0;

	if (phy_id) {
		netdev_dbg(netdev, "Only internal phy supported\n");
		return 0;
	}

	/* Access NSR_LINKST bit for link status instead of MII_BMSR */
	if (loc == MII_BMSR) {
		u8 value;

		sr_read_reg(dev, SR_NSR, &value);
		if (value & NSR_LINKST)
			rc = 1;
	}
	sr_share_read_word(dev, 1, loc, &res);
	if (rc == 1)
		res = le16_to_cpu(res) | BMSR_LSTATUS;
	else
		res = le16_to_cpu(res) & ~BMSR_LSTATUS;

	netdev_dbg(netdev, "sr_mdio_read() phy_id=0x%02x, loc=0x%02x, returns=0x%04x\n",
		   phy_id, loc, res);

	return res;
}