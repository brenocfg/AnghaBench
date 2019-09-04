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
typedef  int u32 ;
struct net_device {int flags; } ;
struct b44 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B44_CAM_CTRL ; 
 scalar_t__ B44_MCAST_TABLE_SIZE ; 
 int /*<<< orphan*/  B44_RXCONFIG ; 
 int CAM_CTRL_ENABLE ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int RXCONFIG_ALLMULTI ; 
 int RXCONFIG_CAM_ABSENT ; 
 int RXCONFIG_PROMISC ; 
 int /*<<< orphan*/  __b44_cam_write (struct b44*,unsigned char*,int) ; 
 int __b44_load_mcast (struct b44*,struct net_device*) ; 
 int /*<<< orphan*/  __b44_set_mac_addr (struct b44*) ; 
 int br32 (struct b44*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bw32 (struct b44*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ netdev_mc_count (struct net_device*) ; 
 struct b44* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void __b44_set_rx_mode(struct net_device *dev)
{
	struct b44 *bp = netdev_priv(dev);
	u32 val;

	val = br32(bp, B44_RXCONFIG);
	val &= ~(RXCONFIG_PROMISC | RXCONFIG_ALLMULTI);
	if ((dev->flags & IFF_PROMISC) || (val & RXCONFIG_CAM_ABSENT)) {
		val |= RXCONFIG_PROMISC;
		bw32(bp, B44_RXCONFIG, val);
	} else {
		unsigned char zero[6] = {0, 0, 0, 0, 0, 0};
		int i = 1;

		__b44_set_mac_addr(bp);

		if ((dev->flags & IFF_ALLMULTI) ||
		    (netdev_mc_count(dev) > B44_MCAST_TABLE_SIZE))
			val |= RXCONFIG_ALLMULTI;
		else
			i = __b44_load_mcast(bp, dev);

		for (; i < 64; i++)
			__b44_cam_write(bp, zero, i);

		bw32(bp, B44_RXCONFIG, val);
        	val = br32(bp, B44_CAM_CTRL);
	        bw32(bp, B44_CAM_CTRL, val | CAM_CTRL_ENABLE);
	}
}