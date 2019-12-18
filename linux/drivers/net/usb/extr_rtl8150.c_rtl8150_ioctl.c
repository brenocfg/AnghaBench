#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct net_device {int dummy; } ;
struct ifreq {int /*<<< orphan*/  ifr_ifru; } ;
struct TYPE_5__ {int phy; } ;
typedef  TYPE_1__ rtl8150_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
#define  SIOCDEVPRIVATE 128 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  read_mii_word (TYPE_1__*,int,int,int*) ; 
 int /*<<< orphan*/  write_mii_word (TYPE_1__*,int,int,int) ; 

__attribute__((used)) static int rtl8150_ioctl(struct net_device *netdev, struct ifreq *rq, int cmd)
{
	rtl8150_t *dev = netdev_priv(netdev);
	u16 *data = (u16 *) & rq->ifr_ifru;
	int res = 0;

	switch (cmd) {
	case SIOCDEVPRIVATE:
		data[0] = dev->phy;
		/* fall through */
	case SIOCDEVPRIVATE + 1:
		read_mii_word(dev, dev->phy, (data[1] & 0x1f), &data[3]);
		break;
	case SIOCDEVPRIVATE + 2:
		if (!capable(CAP_NET_ADMIN))
			return -EPERM;
		write_mii_word(dev, dev->phy, (data[1] & 0x1f), data[2]);
		break;
	default:
		res = -EOPNOTSUPP;
	}

	return res;
}