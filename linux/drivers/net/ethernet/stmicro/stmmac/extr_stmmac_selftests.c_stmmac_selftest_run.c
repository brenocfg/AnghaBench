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
typedef  int u64 ;
struct stmmac_priv {int /*<<< orphan*/  ioaddr; int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/  phydev; } ;
struct ethtool_test {int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int lb; int (* fn ) (struct stmmac_priv*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_TEST_FL_FAILED ; 
 int /*<<< orphan*/  ETH_TEST_FL_OFFLINE ; 
#define  STMMAC_LOOPBACK_MAC 130 
#define  STMMAC_LOOPBACK_NONE 129 
#define  STMMAC_LOOPBACK_PHY 128 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int phy_loopback (int /*<<< orphan*/ ,int) ; 
 int stmmac_selftest_get_count (struct stmmac_priv*) ; 
 TYPE_1__* stmmac_selftests ; 
 int stmmac_set_mac_loopback (struct stmmac_priv*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stmmac_test_next_id ; 
 int stub1 (struct stmmac_priv*) ; 

void stmmac_selftest_run(struct net_device *dev,
			 struct ethtool_test *etest, u64 *buf)
{
	struct stmmac_priv *priv = netdev_priv(dev);
	int count = stmmac_selftest_get_count(priv);
	int carrier = netif_carrier_ok(dev);
	int i, ret;

	memset(buf, 0, sizeof(*buf) * count);
	stmmac_test_next_id = 0;

	if (etest->flags != ETH_TEST_FL_OFFLINE) {
		netdev_err(priv->dev, "Only offline tests are supported\n");
		etest->flags |= ETH_TEST_FL_FAILED;
		return;
	} else if (!carrier) {
		netdev_err(priv->dev, "You need valid Link to execute tests\n");
		etest->flags |= ETH_TEST_FL_FAILED;
		return;
	}

	/* We don't want extra traffic */
	netif_carrier_off(dev);

	/* Wait for queues drain */
	msleep(200);

	for (i = 0; i < count; i++) {
		ret = 0;

		switch (stmmac_selftests[i].lb) {
		case STMMAC_LOOPBACK_PHY:
			ret = -EOPNOTSUPP;
			if (dev->phydev)
				ret = phy_loopback(dev->phydev, true);
			if (!ret)
				break;
			/* Fallthrough */
		case STMMAC_LOOPBACK_MAC:
			ret = stmmac_set_mac_loopback(priv, priv->ioaddr, true);
			break;
		case STMMAC_LOOPBACK_NONE:
			break;
		default:
			ret = -EOPNOTSUPP;
			break;
		}

		/*
		 * First tests will always be MAC / PHY loobpack. If any of
		 * them is not supported we abort earlier.
		 */
		if (ret) {
			netdev_err(priv->dev, "Loopback is not supported\n");
			etest->flags |= ETH_TEST_FL_FAILED;
			break;
		}

		ret = stmmac_selftests[i].fn(priv);
		if (ret && (ret != -EOPNOTSUPP))
			etest->flags |= ETH_TEST_FL_FAILED;
		buf[i] = ret;

		switch (stmmac_selftests[i].lb) {
		case STMMAC_LOOPBACK_PHY:
			ret = -EOPNOTSUPP;
			if (dev->phydev)
				ret = phy_loopback(dev->phydev, false);
			if (!ret)
				break;
			/* Fallthrough */
		case STMMAC_LOOPBACK_MAC:
			stmmac_set_mac_loopback(priv, priv->ioaddr, false);
			break;
		default:
			break;
		}
	}

	/* Restart everything */
	if (carrier)
		netif_carrier_on(dev);
}