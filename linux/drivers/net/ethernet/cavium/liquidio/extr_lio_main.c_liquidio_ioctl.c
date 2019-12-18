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
struct net_device {int dummy; } ;
struct lio {TYPE_1__* oct_dev; } ;
struct ifreq {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ptp_enable; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct lio* GET_LIO (struct net_device*) ; 
#define  SIOCSHWTSTAMP 128 
 int hwtstamp_ioctl (struct net_device*,struct ifreq*) ; 

__attribute__((used)) static int liquidio_ioctl(struct net_device *netdev, struct ifreq *ifr, int cmd)
{
	struct lio *lio = GET_LIO(netdev);

	switch (cmd) {
	case SIOCSHWTSTAMP:
		if (lio->oct_dev->ptp_enable)
			return hwtstamp_ioctl(netdev, ifr);
		/* fall through */
	default:
		return -EOPNOTSUPP;
	}
}