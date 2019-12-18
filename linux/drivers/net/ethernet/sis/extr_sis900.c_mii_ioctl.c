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
struct sis900_private {TYPE_1__* mii; } ;
struct net_device {int dummy; } ;
struct mii_ioctl_data {int phy_id; int reg_num; int /*<<< orphan*/  val_in; int /*<<< orphan*/  val_out; } ;
struct ifreq {int dummy; } ;
struct TYPE_2__ {int phy_addr; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  SIOCGMIIPHY 130 
#define  SIOCGMIIREG 129 
#define  SIOCSMIIREG 128 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 int /*<<< orphan*/  mdio_read (struct net_device*,int,int) ; 
 int /*<<< orphan*/  mdio_write (struct net_device*,int,int,int /*<<< orphan*/ ) ; 
 struct sis900_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mii_ioctl(struct net_device *net_dev, struct ifreq *rq, int cmd)
{
	struct sis900_private *sis_priv = netdev_priv(net_dev);
	struct mii_ioctl_data *data = if_mii(rq);

	switch(cmd) {
	case SIOCGMIIPHY:		/* Get address of MII PHY in use. */
		data->phy_id = sis_priv->mii->phy_addr;
		/* Fall Through */

	case SIOCGMIIREG:		/* Read MII PHY register. */
		data->val_out = mdio_read(net_dev, data->phy_id & 0x1f, data->reg_num & 0x1f);
		return 0;

	case SIOCSMIIREG:		/* Write MII PHY register. */
		mdio_write(net_dev, data->phy_id & 0x1f, data->reg_num & 0x1f, data->val_in);
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}