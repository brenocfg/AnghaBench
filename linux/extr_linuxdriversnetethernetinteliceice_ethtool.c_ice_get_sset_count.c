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

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETH_SS_STATS 128 
 int ICE_ALL_STATS_LEN (struct net_device*) ; 

__attribute__((used)) static int ice_get_sset_count(struct net_device *netdev, int sset)
{
	switch (sset) {
	case ETH_SS_STATS:
		/* The number (and order) of strings reported *must* remain
		 * constant for a given netdevice. This function must not
		 * report a different number based on run time parameters
		 * (such as the number of queues in use, or the setting of
		 * a private ethtool flag). This is due to the nature of the
		 * ethtool stats API.
		 *
		 * User space programs such as ethtool must make 3 separate
		 * ioctl requests, one for size, one for the strings, and
		 * finally one for the stats. Since these cross into
		 * user space, changes to the number or size could result in
		 * undefined memory access or incorrect string<->value
		 * correlations for statistics.
		 *
		 * Even if it appears to be safe, changes to the size or
		 * order of strings will suffer from race conditions and are
		 * not safe.
		 */
		return ICE_ALL_STATS_LEN(netdev);
	default:
		return -EOPNOTSUPP;
	}
}