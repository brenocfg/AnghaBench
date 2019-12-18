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
typedef  int u16 ;
struct net_device {int dummy; } ;
struct mii_ioctl_data {int val_in; } ;
struct jme_adapter {int /*<<< orphan*/  flags; int /*<<< orphan*/  old_cmd; int /*<<< orphan*/  phy_lock; int /*<<< orphan*/  mii_if; } ;
struct ifreq {int dummy; } ;

/* Variables and functions */
 int BMCR_ANENABLE ; 
 int BMCR_RESET ; 
 int BMCR_SPEED1000 ; 
 int EINVAL ; 
 int /*<<< orphan*/  JME_FLAG_SSET ; 
 int SIOCSMIIREG ; 
 int generic_mii_ioctl (int /*<<< orphan*/ *,struct mii_ioctl_data*,int,unsigned int*) ; 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 int /*<<< orphan*/  jme_get_link_ksettings (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jme_reset_link (struct jme_adapter*) ; 
 struct jme_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
jme_ioctl(struct net_device *netdev, struct ifreq *rq, int cmd)
{
	int rc;
	struct jme_adapter *jme = netdev_priv(netdev);
	struct mii_ioctl_data *mii_data = if_mii(rq);
	unsigned int duplex_chg;

	if (cmd == SIOCSMIIREG) {
		u16 val = mii_data->val_in;
		if (!(val & (BMCR_RESET|BMCR_ANENABLE)) &&
		    (val & BMCR_SPEED1000))
			return -EINVAL;
	}

	spin_lock_bh(&jme->phy_lock);
	rc = generic_mii_ioctl(&jme->mii_if, mii_data, cmd, &duplex_chg);
	spin_unlock_bh(&jme->phy_lock);

	if (!rc && (cmd == SIOCSMIIREG)) {
		if (duplex_chg)
			jme_reset_link(jme);
		jme_get_link_ksettings(netdev, &jme->old_cmd);
		set_bit(JME_FLAG_SSET, &jme->flags);
	}

	return rc;
}