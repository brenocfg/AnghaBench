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
typedef  int /*<<< orphan*/  u32 ;
struct tg3 {int phy_flags; int phy_addr; int /*<<< orphan*/  lock; int /*<<< orphan*/  mdio_bus; } ;
struct phy_device {int dummy; } ;
struct net_device {int dummy; } ;
struct mii_ioctl_data {int phy_id; int reg_num; int /*<<< orphan*/  val_in; int /*<<< orphan*/  val_out; } ;
struct ifreq {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EOPNOTSUPP ; 
#define  SIOCGHWTSTAMP 132 
#define  SIOCGMIIPHY 131 
#define  SIOCGMIIREG 130 
#define  SIOCSHWTSTAMP 129 
#define  SIOCSMIIREG 128 
 int TG3_PHYFLG_IS_CONNECTED ; 
 int TG3_PHYFLG_PHY_SERDES ; 
 int /*<<< orphan*/  USE_PHYLIB ; 
 int __tg3_readphy (struct tg3*,int,int,int /*<<< orphan*/ *) ; 
 int __tg3_writephy (struct tg3*,int,int,int /*<<< orphan*/ ) ; 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 struct phy_device* mdiobus_get_phy (int /*<<< orphan*/ ,int) ; 
 struct tg3* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int phy_mii_ioctl (struct phy_device*,struct ifreq*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 int tg3_hwtstamp_get (struct net_device*,struct ifreq*) ; 
 int tg3_hwtstamp_set (struct net_device*,struct ifreq*) ; 

__attribute__((used)) static int tg3_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	struct mii_ioctl_data *data = if_mii(ifr);
	struct tg3 *tp = netdev_priv(dev);
	int err;

	if (tg3_flag(tp, USE_PHYLIB)) {
		struct phy_device *phydev;
		if (!(tp->phy_flags & TG3_PHYFLG_IS_CONNECTED))
			return -EAGAIN;
		phydev = mdiobus_get_phy(tp->mdio_bus, tp->phy_addr);
		return phy_mii_ioctl(phydev, ifr, cmd);
	}

	switch (cmd) {
	case SIOCGMIIPHY:
		data->phy_id = tp->phy_addr;

		/* fall through */
	case SIOCGMIIREG: {
		u32 mii_regval;

		if (tp->phy_flags & TG3_PHYFLG_PHY_SERDES)
			break;			/* We have no PHY */

		if (!netif_running(dev))
			return -EAGAIN;

		spin_lock_bh(&tp->lock);
		err = __tg3_readphy(tp, data->phy_id & 0x1f,
				    data->reg_num & 0x1f, &mii_regval);
		spin_unlock_bh(&tp->lock);

		data->val_out = mii_regval;

		return err;
	}

	case SIOCSMIIREG:
		if (tp->phy_flags & TG3_PHYFLG_PHY_SERDES)
			break;			/* We have no PHY */

		if (!netif_running(dev))
			return -EAGAIN;

		spin_lock_bh(&tp->lock);
		err = __tg3_writephy(tp, data->phy_id & 0x1f,
				     data->reg_num & 0x1f, data->val_in);
		spin_unlock_bh(&tp->lock);

		return err;

	case SIOCSHWTSTAMP:
		return tg3_hwtstamp_set(dev, ifr);

	case SIOCGHWTSTAMP:
		return tg3_hwtstamp_get(dev, ifr);

	default:
		/* do nothing */
		break;
	}
	return -EOPNOTSUPP;
}