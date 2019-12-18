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
struct ifreq {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int SIOCGHWTSTAMP ; 
 int SIOCSHWTSTAMP ; 
 int enetc_hwtstamp_get (struct net_device*,struct ifreq*) ; 
 int enetc_hwtstamp_set (struct net_device*,struct ifreq*) ; 

int enetc_ioctl(struct net_device *ndev, struct ifreq *rq, int cmd)
{
#ifdef CONFIG_FSL_ENETC_HW_TIMESTAMPING
	if (cmd == SIOCSHWTSTAMP)
		return enetc_hwtstamp_set(ndev, rq);
	if (cmd == SIOCGHWTSTAMP)
		return enetc_hwtstamp_get(ndev, rq);
#endif
	return -EINVAL;
}