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
 int e1000_mii_ioctl (struct net_device*,struct ifreq*,int) ; 
 int e1000e_hwtstamp_get (struct net_device*,struct ifreq*) ; 
 int e1000e_hwtstamp_set (struct net_device*,struct ifreq*) ; 

__attribute__((used)) static int e1000_ioctl(struct net_device *netdev, struct ifreq *ifr, int cmd)
{
	switch (cmd) {
	case SIOCGMIIPHY:
	case SIOCGMIIREG:
	case SIOCSMIIREG:
		return e1000_mii_ioctl(netdev, ifr, cmd);
	case SIOCSHWTSTAMP:
		return e1000e_hwtstamp_set(netdev, ifr);
	case SIOCGHWTSTAMP:
		return e1000e_hwtstamp_get(netdev, ifr);
	default:
		return -EOPNOTSUPP;
	}
}