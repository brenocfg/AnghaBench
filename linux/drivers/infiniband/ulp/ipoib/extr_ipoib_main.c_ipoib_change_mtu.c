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
struct net_device {int mtu; } ;
struct ipoib_dev_priv {int mcast_mtu; int admin_mtu; TYPE_1__* rn_ops; int /*<<< orphan*/  max_ib_mtu; } ;
struct TYPE_2__ {int (* ndo_change_mtu ) (struct net_device*,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ETH_MIN_MTU ; 
 int IPOIB_ENCAP_LEN ; 
 int IPOIB_UD_MTU (int /*<<< orphan*/ ) ; 
 scalar_t__ ipoib_cm_admin_enabled (struct net_device*) ; 
 int ipoib_cm_max_mtu (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_dbg (struct ipoib_dev_priv*,char*,int) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int stub1 (struct net_device*,int) ; 

__attribute__((used)) static int ipoib_change_mtu(struct net_device *dev, int new_mtu)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);
	int ret = 0;

	/* dev->mtu > 2K ==> connected mode */
	if (ipoib_cm_admin_enabled(dev)) {
		if (new_mtu > ipoib_cm_max_mtu(dev))
			return -EINVAL;

		if (new_mtu > priv->mcast_mtu)
			ipoib_warn(priv, "mtu > %d will cause multicast packet drops.\n",
				   priv->mcast_mtu);

		dev->mtu = new_mtu;
		return 0;
	}

	if (new_mtu < (ETH_MIN_MTU + IPOIB_ENCAP_LEN) ||
	    new_mtu > IPOIB_UD_MTU(priv->max_ib_mtu))
		return -EINVAL;

	priv->admin_mtu = new_mtu;

	if (priv->mcast_mtu < priv->admin_mtu)
		ipoib_dbg(priv, "MTU must be smaller than the underlying "
				"link layer MTU - 4 (%u)\n", priv->mcast_mtu);

	new_mtu = min(priv->mcast_mtu, priv->admin_mtu);

	if (priv->rn_ops->ndo_change_mtu) {
		bool carrier_status = netif_carrier_ok(dev);

		netif_carrier_off(dev);

		/* notify lower level on the real mtu */
		ret = priv->rn_ops->ndo_change_mtu(dev, new_mtu);

		if (carrier_status)
			netif_carrier_on(dev);
	} else {
		dev->mtu = new_mtu;
	}

	return ret;
}