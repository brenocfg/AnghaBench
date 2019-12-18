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
#define  SIOCGHWTSTAMP 129 
#define  SIOCSHWTSTAMP 128 
 int mlx4_en_hwtstamp_get (struct net_device*,struct ifreq*) ; 
 int mlx4_en_hwtstamp_set (struct net_device*,struct ifreq*) ; 

__attribute__((used)) static int mlx4_en_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	switch (cmd) {
	case SIOCSHWTSTAMP:
		return mlx4_en_hwtstamp_set(dev, ifr);
	case SIOCGHWTSTAMP:
		return mlx4_en_hwtstamp_get(dev, ifr);
	default:
		return -EOPNOTSUPP;
	}
}