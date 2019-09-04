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
struct qede_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct ifreq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qede_dev*,int /*<<< orphan*/ ,char*,int) ; 
 int EAGAIN ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  QED_MSG_DEBUG ; 
#define  SIOCSHWTSTAMP 128 
 struct qede_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int qede_ptp_hw_ts (struct qede_dev*,struct ifreq*) ; 

__attribute__((used)) static int qede_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	struct qede_dev *edev = netdev_priv(dev);

	if (!netif_running(dev))
		return -EAGAIN;

	switch (cmd) {
	case SIOCSHWTSTAMP:
		return qede_ptp_hw_ts(edev, ifr);
	default:
		DP_VERBOSE(edev, QED_MSG_DEBUG,
			   "default IOCTL cmd 0x%x\n", cmd);
		return -EOPNOTSUPP;
	}

	return 0;
}