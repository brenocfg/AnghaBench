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
struct net_device {int dummy; } ;
struct mii_ioctl_data {int phy_id; int reg_num; int /*<<< orphan*/  val_in; int /*<<< orphan*/  val_out; } ;
struct ifreq {int dummy; } ;
struct gem {int mii_phy_addr; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  SIOCGMIIPHY 130 
#define  SIOCGMIIREG 129 
#define  SIOCSMIIREG 128 
 int /*<<< orphan*/  __sungem_phy_read (struct gem*,int,int) ; 
 int /*<<< orphan*/  __sungem_phy_write (struct gem*,int,int,int /*<<< orphan*/ ) ; 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 struct gem* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int gem_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	struct gem *gp = netdev_priv(dev);
	struct mii_ioctl_data *data = if_mii(ifr);
	int rc = -EOPNOTSUPP;

	/* For SIOCGMIIREG and SIOCSMIIREG the core checks for us that
	 * netif_device_present() is true and holds rtnl_lock for us
	 * so we have nothing to worry about
	 */

	switch (cmd) {
	case SIOCGMIIPHY:		/* Get address of MII PHY in use. */
		data->phy_id = gp->mii_phy_addr;
		/* Fallthrough... */

	case SIOCGMIIREG:		/* Read MII PHY register. */
		data->val_out = __sungem_phy_read(gp, data->phy_id & 0x1f,
					   data->reg_num & 0x1f);
		rc = 0;
		break;

	case SIOCSMIIREG:		/* Write MII PHY register. */
		__sungem_phy_write(gp, data->phy_id & 0x1f, data->reg_num & 0x1f,
			    data->val_in);
		rc = 0;
		break;
	}
	return rc;
}