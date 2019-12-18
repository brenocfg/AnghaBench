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
typedef  int u8 ;
struct usbnet {int dummy; } ;
struct net_device {int dummy; } ;
struct ethtool_wolinfo {int supported; int wolopts; } ;

/* Variables and functions */
 int /*<<< orphan*/  AX_CMD_READ_MONITOR_MODE ; 
 int AX_MONITOR_LINK ; 
 int AX_MONITOR_MAGIC ; 
 int WAKE_MAGIC ; 
 int WAKE_PHY ; 
 scalar_t__ asix_read_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 struct usbnet* netdev_priv (struct net_device*) ; 

void asix_get_wol(struct net_device *net, struct ethtool_wolinfo *wolinfo)
{
	struct usbnet *dev = netdev_priv(net);
	u8 opt;

	if (asix_read_cmd(dev, AX_CMD_READ_MONITOR_MODE,
			  0, 0, 1, &opt, 0) < 0) {
		wolinfo->supported = 0;
		wolinfo->wolopts = 0;
		return;
	}
	wolinfo->supported = WAKE_PHY | WAKE_MAGIC;
	wolinfo->wolopts = 0;
	if (opt & AX_MONITOR_LINK)
		wolinfo->wolopts |= WAKE_PHY;
	if (opt & AX_MONITOR_MAGIC)
		wolinfo->wolopts |= WAKE_MAGIC;
}