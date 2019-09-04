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
struct net_device {int dummy; } ;
struct mii_ioctl_data {int reg_num; int val_out; int /*<<< orphan*/  phy_id; } ;
struct ifreq {int dummy; } ;
struct TYPE_6__ {int bmcr; int bmsr; int advertise; int lpa; int expansion; int ctrl1000; int stat1000; int estatus; } ;
struct TYPE_4__ {scalar_t__ media_type; int id; int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {TYPE_1__ phy; } ;
struct e1000_adapter {TYPE_3__ phy_regs; TYPE_2__ hw; } ;

/* Variables and functions */
 int EIO ; 
 int EOPNOTSUPP ; 
#define  MII_ADVERTISE 140 
#define  MII_BMCR 139 
#define  MII_BMSR 138 
#define  MII_CTRL1000 137 
#define  MII_ESTATUS 136 
#define  MII_EXPANSION 135 
#define  MII_LPA 134 
#define  MII_PHYSID1 133 
#define  MII_PHYSID2 132 
#define  MII_STAT1000 131 
#define  SIOCGMIIPHY 130 
#define  SIOCGMIIREG 129 
#define  SIOCSMIIREG 128 
 scalar_t__ e1000_media_type_copper ; 
 int /*<<< orphan*/  e1000_phy_read_status (struct e1000_adapter*) ; 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int e1000_mii_ioctl(struct net_device *netdev, struct ifreq *ifr,
			   int cmd)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct mii_ioctl_data *data = if_mii(ifr);

	if (adapter->hw.phy.media_type != e1000_media_type_copper)
		return -EOPNOTSUPP;

	switch (cmd) {
	case SIOCGMIIPHY:
		data->phy_id = adapter->hw.phy.addr;
		break;
	case SIOCGMIIREG:
		e1000_phy_read_status(adapter);

		switch (data->reg_num & 0x1F) {
		case MII_BMCR:
			data->val_out = adapter->phy_regs.bmcr;
			break;
		case MII_BMSR:
			data->val_out = adapter->phy_regs.bmsr;
			break;
		case MII_PHYSID1:
			data->val_out = (adapter->hw.phy.id >> 16);
			break;
		case MII_PHYSID2:
			data->val_out = (adapter->hw.phy.id & 0xFFFF);
			break;
		case MII_ADVERTISE:
			data->val_out = adapter->phy_regs.advertise;
			break;
		case MII_LPA:
			data->val_out = adapter->phy_regs.lpa;
			break;
		case MII_EXPANSION:
			data->val_out = adapter->phy_regs.expansion;
			break;
		case MII_CTRL1000:
			data->val_out = adapter->phy_regs.ctrl1000;
			break;
		case MII_STAT1000:
			data->val_out = adapter->phy_regs.stat1000;
			break;
		case MII_ESTATUS:
			data->val_out = adapter->phy_regs.estatus;
			break;
		default:
			return -EIO;
		}
		break;
	case SIOCSMIIREG:
	default:
		return -EOPNOTSUPP;
	}
	return 0;
}