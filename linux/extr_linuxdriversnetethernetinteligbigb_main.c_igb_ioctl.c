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
 int EOPNOTSUPP ; 
#define  SIOCGHWTSTAMP 132 
#define  SIOCGMIIPHY 131 
#define  SIOCGMIIREG 130 
#define  SIOCSHWTSTAMP 129 
#define  SIOCSMIIREG 128 
 int igb_mii_ioctl (struct net_device*,struct ifreq*,int) ; 
 int igb_ptp_get_ts_config (struct net_device*,struct ifreq*) ; 
 int igb_ptp_set_ts_config (struct net_device*,struct ifreq*) ; 

__attribute__((used)) static int igb_ioctl(struct net_device *netdev, struct ifreq *ifr, int cmd)
{
	switch (cmd) {
	case SIOCGMIIPHY:
	case SIOCGMIIREG:
	case SIOCSMIIREG:
		return igb_mii_ioctl(netdev, ifr, cmd);
	case SIOCGHWTSTAMP:
		return igb_ptp_get_ts_config(netdev, ifr);
	case SIOCSHWTSTAMP:
		return igb_ptp_set_ts_config(netdev, ifr);
	default:
		return -EOPNOTSUPP;
	}
}