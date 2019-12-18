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
struct netdev_private {int phy_addr_external; int /*<<< orphan*/  advertising; } ;
struct net_device {int /*<<< orphan*/  if_port; } ;
struct mii_ioctl_data {int phy_id; int reg_num; int /*<<< orphan*/  val_in; int /*<<< orphan*/  val_out; } ;
struct ifreq {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int MII_ADVERTISE ; 
 int /*<<< orphan*/  PORT_TP ; 
#define  SIOCGMIIPHY 130 
#define  SIOCGMIIREG 129 
#define  SIOCSMIIREG 128 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 int /*<<< orphan*/  mdio_read (struct net_device*,int) ; 
 int /*<<< orphan*/  mdio_write (struct net_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  miiport_read (struct net_device*,int,int) ; 
 int /*<<< orphan*/  miiport_write (struct net_device*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  move_int_phy (struct net_device*,int) ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int netdev_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	struct mii_ioctl_data *data = if_mii(rq);
	struct netdev_private *np = netdev_priv(dev);

	switch(cmd) {
	case SIOCGMIIPHY:		/* Get address of MII PHY in use. */
		data->phy_id = np->phy_addr_external;
		/* Fall Through */

	case SIOCGMIIREG:		/* Read MII PHY register. */
		/* The phy_id is not enough to uniquely identify
		 * the intended target. Therefore the command is sent to
		 * the given mii on the current port.
		 */
		if (dev->if_port == PORT_TP) {
			if ((data->phy_id & 0x1f) == np->phy_addr_external)
				data->val_out = mdio_read(dev,
							data->reg_num & 0x1f);
			else
				data->val_out = 0;
		} else {
			move_int_phy(dev, data->phy_id & 0x1f);
			data->val_out = miiport_read(dev, data->phy_id & 0x1f,
							data->reg_num & 0x1f);
		}
		return 0;

	case SIOCSMIIREG:		/* Write MII PHY register. */
		if (dev->if_port == PORT_TP) {
			if ((data->phy_id & 0x1f) == np->phy_addr_external) {
 				if ((data->reg_num & 0x1f) == MII_ADVERTISE)
					np->advertising = data->val_in;
				mdio_write(dev, data->reg_num & 0x1f,
							data->val_in);
			}
		} else {
			if ((data->phy_id & 0x1f) == np->phy_addr_external) {
 				if ((data->reg_num & 0x1f) == MII_ADVERTISE)
					np->advertising = data->val_in;
			}
			move_int_phy(dev, data->phy_id & 0x1f);
			miiport_write(dev, data->phy_id & 0x1f,
						data->reg_num & 0x1f,
						data->val_in);
		}
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}