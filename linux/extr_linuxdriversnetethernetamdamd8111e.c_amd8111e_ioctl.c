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
struct net_device {int dummy; } ;
struct mii_ioctl_data {int reg_num; int /*<<< orphan*/  val_in; int /*<<< orphan*/  phy_id; int /*<<< orphan*/  val_out; } ;
struct ifreq {int dummy; } ;
struct amd8111e_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  ext_phy_addr; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int PHY_REG_ADDR_MASK ; 
#define  SIOCGMIIPHY 130 
#define  SIOCGMIIREG 129 
#define  SIOCSMIIREG 128 
 int amd8111e_read_phy (struct amd8111e_priv*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int amd8111e_write_phy (struct amd8111e_priv*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 struct amd8111e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amd8111e_ioctl(struct net_device *dev , struct ifreq *ifr, int cmd)
{
	struct mii_ioctl_data *data = if_mii(ifr);
	struct amd8111e_priv *lp = netdev_priv(dev);
	int err;
	u32 mii_regval;

	switch(cmd) {
	case SIOCGMIIPHY:
		data->phy_id = lp->ext_phy_addr;

	/* fallthru */
	case SIOCGMIIREG:

		spin_lock_irq(&lp->lock);
		err = amd8111e_read_phy(lp, data->phy_id,
			data->reg_num & PHY_REG_ADDR_MASK, &mii_regval);
		spin_unlock_irq(&lp->lock);

		data->val_out = mii_regval;
		return err;

	case SIOCSMIIREG:

		spin_lock_irq(&lp->lock);
		err = amd8111e_write_phy(lp, data->phy_id,
			data->reg_num & PHY_REG_ADDR_MASK, data->val_in);
		spin_unlock_irq(&lp->lock);

		return err;

	default:
		/* do nothing */
		break;
	}
	return -EOPNOTSUPP;
}