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
struct stmmac_priv {int /*<<< orphan*/  phylink; } ;
struct net_device {int dummy; } ;
struct ifreq {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  SIOCGHWTSTAMP 132 
#define  SIOCGMIIPHY 131 
#define  SIOCGMIIREG 130 
#define  SIOCSHWTSTAMP 129 
#define  SIOCSMIIREG 128 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int phylink_mii_ioctl (int /*<<< orphan*/ ,struct ifreq*,int) ; 
 int stmmac_hwtstamp_get (struct net_device*,struct ifreq*) ; 
 int stmmac_hwtstamp_set (struct net_device*,struct ifreq*) ; 

__attribute__((used)) static int stmmac_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	struct stmmac_priv *priv = netdev_priv (dev);
	int ret = -EOPNOTSUPP;

	if (!netif_running(dev))
		return -EINVAL;

	switch (cmd) {
	case SIOCGMIIPHY:
	case SIOCGMIIREG:
	case SIOCSMIIREG:
		ret = phylink_mii_ioctl(priv->phylink, rq, cmd);
		break;
	case SIOCSHWTSTAMP:
		ret = stmmac_hwtstamp_set(dev, rq);
		break;
	case SIOCGHWTSTAMP:
		ret = stmmac_hwtstamp_get(dev, rq);
		break;
	default:
		break;
	}

	return ret;
}