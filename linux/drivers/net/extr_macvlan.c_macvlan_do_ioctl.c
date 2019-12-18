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
struct net_device_ops {int (* ndo_do_ioctl ) (struct net_device*,struct ifreq*,int) ;} ;
struct net_device {int /*<<< orphan*/  name; struct net_device_ops* netdev_ops; } ;
struct ifreq {int /*<<< orphan*/  ifr_ifru; int /*<<< orphan*/  ifr_name; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
#define  SIOCGHWTSTAMP 129 
#define  SIOCSHWTSTAMP 128 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  init_net ; 
 struct net_device* macvlan_dev_real_dev (struct net_device*) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_device_present (struct net_device*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct net_device*,struct ifreq*,int) ; 

__attribute__((used)) static int macvlan_do_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	struct net_device *real_dev = macvlan_dev_real_dev(dev);
	const struct net_device_ops *ops = real_dev->netdev_ops;
	struct ifreq ifrr;
	int err = -EOPNOTSUPP;

	strscpy(ifrr.ifr_name, real_dev->name, IFNAMSIZ);
	ifrr.ifr_ifru = ifr->ifr_ifru;

	switch (cmd) {
	case SIOCSHWTSTAMP:
		if (!net_eq(dev_net(dev), &init_net))
			break;
		/* fall through */
	case SIOCGHWTSTAMP:
		if (netif_device_present(real_dev) && ops->ndo_do_ioctl)
			err = ops->ndo_do_ioctl(real_dev, &ifrr, cmd);
		break;
	}

	if (!err)
		ifr->ifr_ifru = ifrr.ifr_ifru;

	return err;
}