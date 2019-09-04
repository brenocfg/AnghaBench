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
struct pcnet_dev {int flags; int /*<<< orphan*/  phy_id; } ;
struct net_device {unsigned int base_addr; } ;
struct mii_ioctl_data {int reg_num; int /*<<< orphan*/  val_in; int /*<<< orphan*/  phy_id; int /*<<< orphan*/  val_out; } ;
struct ifreq {int dummy; } ;

/* Variables and functions */
 unsigned int DLINK_GPIO ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int IS_DL10019 ; 
 int IS_DL10022 ; 
 struct pcnet_dev* PRIV (struct net_device*) ; 
#define  SIOCGMIIPHY 130 
#define  SIOCGMIIREG 129 
#define  SIOCSMIIREG 128 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 int /*<<< orphan*/  mdio_read (unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdio_write (unsigned int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ei_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
    struct pcnet_dev *info = PRIV(dev);
    struct mii_ioctl_data *data = if_mii(rq);
    unsigned int mii_addr = dev->base_addr + DLINK_GPIO;

    if (!(info->flags & (IS_DL10019|IS_DL10022)))
	return -EINVAL;

    switch (cmd) {
    case SIOCGMIIPHY:
	data->phy_id = info->phy_id;
	/* fall through */
    case SIOCGMIIREG:		/* Read MII PHY register. */
	data->val_out = mdio_read(mii_addr, data->phy_id, data->reg_num & 0x1f);
	return 0;
    case SIOCSMIIREG:		/* Write MII PHY register. */
	mdio_write(mii_addr, data->phy_id, data->reg_num & 0x1f, data->val_in);
	return 0;
    }
    return -EOPNOTSUPP;
}