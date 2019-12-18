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
struct usbnet {int /*<<< orphan*/  net; scalar_t__* data; } ;
struct smsc75xx_priv {int rfe_ctl; int /*<<< orphan*/  rfe_ctl_lock; } ;
struct net_device {int dummy; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  RFE_CTL ; 
 int RFE_CTL_IP_CKM ; 
 int RFE_CTL_TCPUDP_CKM ; 
 struct usbnet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 
 int smsc75xx_write_reg (struct usbnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int smsc75xx_set_features(struct net_device *netdev,
	netdev_features_t features)
{
	struct usbnet *dev = netdev_priv(netdev);
	struct smsc75xx_priv *pdata = (struct smsc75xx_priv *)(dev->data[0]);
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&pdata->rfe_ctl_lock, flags);

	if (features & NETIF_F_RXCSUM)
		pdata->rfe_ctl |= RFE_CTL_TCPUDP_CKM | RFE_CTL_IP_CKM;
	else
		pdata->rfe_ctl &= ~(RFE_CTL_TCPUDP_CKM | RFE_CTL_IP_CKM);

	spin_unlock_irqrestore(&pdata->rfe_ctl_lock, flags);
	/* it's racing here! */

	ret = smsc75xx_write_reg(dev, RFE_CTL, pdata->rfe_ctl);
	if (ret < 0) {
		netdev_warn(dev->net, "Error writing RFE_CTL\n");
		return ret;
	}
	return 0;
}