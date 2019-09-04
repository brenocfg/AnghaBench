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
struct net_device {int dummy; } ;
struct mii_ioctl_data {int reg_num; int /*<<< orphan*/  val_in; int /*<<< orphan*/  phy_id; int /*<<< orphan*/  val_out; } ;
struct ksz_port {TYPE_1__* linked; } ;
struct ksz_hw {int dummy; } ;
struct ifreq {int dummy; } ;
struct dev_priv {int /*<<< orphan*/  proc_sem; int /*<<< orphan*/  id; struct ksz_port port; struct dev_info* adapter; } ;
struct dev_info {struct ksz_hw hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  port_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EIO ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int ERESTARTSYS ; 
#define  SIOCGMIIPHY 130 
#define  SIOCGMIIREG 129 
#define  SIOCSMIIREG 128 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 scalar_t__ down_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hw_r_phy (struct ksz_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hw_w_phy (struct ksz_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 struct dev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int netdev_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;
	struct ksz_port *port = &priv->port;
	int result = 0;
	struct mii_ioctl_data *data = if_mii(ifr);

	if (down_interruptible(&priv->proc_sem))
		return -ERESTARTSYS;

	switch (cmd) {
	/* Get address of MII PHY in use. */
	case SIOCGMIIPHY:
		data->phy_id = priv->id;

		/* Fallthrough... */

	/* Read MII PHY register. */
	case SIOCGMIIREG:
		if (data->phy_id != priv->id || data->reg_num >= 6)
			result = -EIO;
		else
			hw_r_phy(hw, port->linked->port_id, data->reg_num,
				&data->val_out);
		break;

	/* Write MII PHY register. */
	case SIOCSMIIREG:
		if (!capable(CAP_NET_ADMIN))
			result = -EPERM;
		else if (data->phy_id != priv->id || data->reg_num >= 6)
			result = -EIO;
		else
			hw_w_phy(hw, port->linked->port_id, data->reg_num,
				data->val_in);
		break;

	default:
		result = -EOPNOTSUPP;
	}

	up(&priv->proc_sem);

	return result;
}