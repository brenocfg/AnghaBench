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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct mii_ioctl_data {int /*<<< orphan*/  val_in; int /*<<< orphan*/  reg_num; int /*<<< orphan*/  phy_id; int /*<<< orphan*/  val_out; } ;
struct ifreq {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  phy_addr; } ;
struct bnxt {TYPE_1__ link_info; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EOPNOTSUPP ; 
#define  SIOCGMIIPHY 130 
#define  SIOCGMIIREG 129 
#define  SIOCSMIIREG 128 
 int bnxt_hwrm_port_phy_read (struct bnxt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bnxt_hwrm_port_phy_write (struct bnxt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 

__attribute__((used)) static int bnxt_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	struct mii_ioctl_data *mdio = if_mii(ifr);
	struct bnxt *bp = netdev_priv(dev);
	int rc;

	switch (cmd) {
	case SIOCGMIIPHY:
		mdio->phy_id = bp->link_info.phy_addr;

		/* fallthru */
	case SIOCGMIIREG: {
		u16 mii_regval = 0;

		if (!netif_running(dev))
			return -EAGAIN;

		rc = bnxt_hwrm_port_phy_read(bp, mdio->phy_id, mdio->reg_num,
					     &mii_regval);
		mdio->val_out = mii_regval;
		return rc;
	}

	case SIOCSMIIREG:
		if (!netif_running(dev))
			return -EAGAIN;

		return bnxt_hwrm_port_phy_write(bp, mdio->phy_id, mdio->reg_num,
						mdio->val_in);

	default:
		/* do nothing */
		break;
	}
	return -EOPNOTSUPP;
}