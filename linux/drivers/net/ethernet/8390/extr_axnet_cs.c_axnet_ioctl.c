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
struct net_device {unsigned int base_addr; } ;
struct mii_ioctl_data {int reg_num; int /*<<< orphan*/  val_in; int /*<<< orphan*/  phy_id; int /*<<< orphan*/  val_out; } ;
struct ifreq {int dummy; } ;
struct axnet_dev {int /*<<< orphan*/  phy_id; } ;

/* Variables and functions */
 unsigned int AXNET_MII_EEP ; 
 int EOPNOTSUPP ; 
 struct axnet_dev* PRIV (struct net_device*) ; 
#define  SIOCGMIIPHY 130 
#define  SIOCGMIIREG 129 
#define  SIOCSMIIREG 128 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 int /*<<< orphan*/  mdio_read (unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdio_write (unsigned int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int axnet_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
    struct axnet_dev *info = PRIV(dev);
    struct mii_ioctl_data *data = if_mii(rq);
    unsigned int mii_addr = dev->base_addr + AXNET_MII_EEP;
    switch (cmd) {
    case SIOCGMIIPHY:
	data->phy_id = info->phy_id;
	/* Fall through */
    case SIOCGMIIREG:		/* Read MII PHY register. */
	data->val_out = mdio_read(mii_addr, data->phy_id, data->reg_num & 0x1f);
	return 0;
    case SIOCSMIIREG:		/* Write MII PHY register. */
	mdio_write(mii_addr, data->phy_id, data->reg_num & 0x1f, data->val_in);
	return 0;
    }
    return -EOPNOTSUPP;
}