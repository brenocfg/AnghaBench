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
struct xgbe_prv_data {int dummy; } ;
struct net_device {int dummy; } ;
struct ifreq {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  SIOCGHWTSTAMP 129 
#define  SIOCSHWTSTAMP 128 
 struct xgbe_prv_data* netdev_priv (struct net_device*) ; 
 int xgbe_get_hwtstamp_settings (struct xgbe_prv_data*,struct ifreq*) ; 
 int xgbe_set_hwtstamp_settings (struct xgbe_prv_data*,struct ifreq*) ; 

__attribute__((used)) static int xgbe_ioctl(struct net_device *netdev, struct ifreq *ifreq, int cmd)
{
	struct xgbe_prv_data *pdata = netdev_priv(netdev);
	int ret;

	switch (cmd) {
	case SIOCGHWTSTAMP:
		ret = xgbe_get_hwtstamp_settings(pdata, ifreq);
		break;

	case SIOCSHWTSTAMP:
		ret = xgbe_set_hwtstamp_settings(pdata, ifreq);
		break;

	default:
		ret = -EOPNOTSUPP;
	}

	return ret;
}