#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  mtu; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  send_flags; } ;
struct TYPE_4__ {TYPE_1__ wr; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  mcast_mtu; int /*<<< orphan*/  flags; TYPE_2__ tx_wr; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  IB_SEND_IP_CSUM ; 
 scalar_t__ IPOIB_CM_SUPPORTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPOIB_FLAG_ADMIN_CM ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_mtu (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_cm_max_mtu (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_flush_paths (struct net_device*) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_update_features (struct net_device*) ; 
 int /*<<< orphan*/  rtnl_trylock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ipoib_set_mode(struct net_device *dev, const char *buf)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);

	if ((test_bit(IPOIB_FLAG_ADMIN_CM, &priv->flags) &&
	     !strcmp(buf, "connected\n")) ||
	     (!test_bit(IPOIB_FLAG_ADMIN_CM, &priv->flags) &&
	     !strcmp(buf, "datagram\n"))) {
		return 0;
	}

	/* flush paths if we switch modes so that connections are restarted */
	if (IPOIB_CM_SUPPORTED(dev->dev_addr) && !strcmp(buf, "connected\n")) {
		set_bit(IPOIB_FLAG_ADMIN_CM, &priv->flags);
		ipoib_warn(priv, "enabling connected mode "
			   "will cause multicast packet drops\n");
		netdev_update_features(dev);
		dev_set_mtu(dev, ipoib_cm_max_mtu(dev));
		rtnl_unlock();
		priv->tx_wr.wr.send_flags &= ~IB_SEND_IP_CSUM;

		ipoib_flush_paths(dev);
		return (!rtnl_trylock()) ? -EBUSY : 0;
	}

	if (!strcmp(buf, "datagram\n")) {
		clear_bit(IPOIB_FLAG_ADMIN_CM, &priv->flags);
		netdev_update_features(dev);
		dev_set_mtu(dev, min(priv->mcast_mtu, dev->mtu));
		rtnl_unlock();
		ipoib_flush_paths(dev);
		return (!rtnl_trylock()) ? -EBUSY : 0;
	}

	return -EINVAL;
}