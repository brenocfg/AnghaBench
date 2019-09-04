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
typedef  int /*<<< orphan*/  u16 ;
struct skge_port {int /*<<< orphan*/  port; struct skge_hw* hw; } ;
struct skge_hw {int /*<<< orphan*/  phy_lock; int /*<<< orphan*/  phy_addr; } ;
struct net_device {int dummy; } ;
struct mii_ioctl_data {int reg_num; int /*<<< orphan*/  val_in; int /*<<< orphan*/  val_out; int /*<<< orphan*/  phy_id; } ;
struct ifreq {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int EOPNOTSUPP ; 
#define  SIOCGMIIPHY 130 
#define  SIOCGMIIREG 129 
#define  SIOCSMIIREG 128 
 int __gm_phy_read (struct skge_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int __xm_phy_read (struct skge_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int gm_phy_write (struct skge_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 int /*<<< orphan*/  is_genesis (struct skge_hw*) ; 
 struct skge_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int xm_phy_write (struct skge_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skge_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	struct mii_ioctl_data *data = if_mii(ifr);
	struct skge_port *skge = netdev_priv(dev);
	struct skge_hw *hw = skge->hw;
	int err = -EOPNOTSUPP;

	if (!netif_running(dev))
		return -ENODEV;	/* Phy still in reset */

	switch (cmd) {
	case SIOCGMIIPHY:
		data->phy_id = hw->phy_addr;

		/* fallthru */
	case SIOCGMIIREG: {
		u16 val = 0;
		spin_lock_bh(&hw->phy_lock);

		if (is_genesis(hw))
			err = __xm_phy_read(hw, skge->port, data->reg_num & 0x1f, &val);
		else
			err = __gm_phy_read(hw, skge->port, data->reg_num & 0x1f, &val);
		spin_unlock_bh(&hw->phy_lock);
		data->val_out = val;
		break;
	}

	case SIOCSMIIREG:
		spin_lock_bh(&hw->phy_lock);
		if (is_genesis(hw))
			err = xm_phy_write(hw, skge->port, data->reg_num & 0x1f,
				   data->val_in);
		else
			err = gm_phy_write(hw, skge->port, data->reg_num & 0x1f,
				   data->val_in);
		spin_unlock_bh(&hw->phy_lock);
		break;
	}
	return err;
}