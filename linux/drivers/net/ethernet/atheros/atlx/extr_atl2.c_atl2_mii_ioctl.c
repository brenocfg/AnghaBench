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
struct mii_ioctl_data {int reg_num; int /*<<< orphan*/  val_in; int /*<<< orphan*/  val_out; int /*<<< orphan*/  phy_id; } ;
struct ifreq {int dummy; } ;
struct atl2_adapter {int /*<<< orphan*/  stats_lock; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int EFAULT ; 
 int EIO ; 
 int EOPNOTSUPP ; 
#define  SIOCGMIIPHY 130 
#define  SIOCGMIIREG 129 
#define  SIOCSMIIREG 128 
 int /*<<< orphan*/  atl2_read_phy_reg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atl2_write_phy_reg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 struct atl2_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int atl2_mii_ioctl(struct net_device *netdev, struct ifreq *ifr, int cmd)
{
	struct atl2_adapter *adapter = netdev_priv(netdev);
	struct mii_ioctl_data *data = if_mii(ifr);
	unsigned long flags;

	switch (cmd) {
	case SIOCGMIIPHY:
		data->phy_id = 0;
		break;
	case SIOCGMIIREG:
		spin_lock_irqsave(&adapter->stats_lock, flags);
		if (atl2_read_phy_reg(&adapter->hw,
			data->reg_num & 0x1F, &data->val_out)) {
			spin_unlock_irqrestore(&adapter->stats_lock, flags);
			return -EIO;
		}
		spin_unlock_irqrestore(&adapter->stats_lock, flags);
		break;
	case SIOCSMIIREG:
		if (data->reg_num & ~(0x1F))
			return -EFAULT;
		spin_lock_irqsave(&adapter->stats_lock, flags);
		if (atl2_write_phy_reg(&adapter->hw, data->reg_num,
			data->val_in)) {
			spin_unlock_irqrestore(&adapter->stats_lock, flags);
			return -EIO;
		}
		spin_unlock_irqrestore(&adapter->stats_lock, flags);
		break;
	default:
		return -EOPNOTSUPP;
	}
	return 0;
}