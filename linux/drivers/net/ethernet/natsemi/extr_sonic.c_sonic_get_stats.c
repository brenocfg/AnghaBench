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
struct net_device_stats {int /*<<< orphan*/  rx_missed_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_crc_errors; } ;
struct sonic_local {struct net_device_stats stats; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SONIC_CRCT ; 
 int /*<<< orphan*/  SONIC_FAET ; 
 int /*<<< orphan*/  SONIC_MPT ; 
 scalar_t__ SONIC_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SONIC_WRITE (int /*<<< orphan*/ ,int) ; 
 struct sonic_local* netdev_priv (struct net_device*) ; 

__attribute__((used)) static struct net_device_stats *sonic_get_stats(struct net_device *dev)
{
	struct sonic_local *lp = netdev_priv(dev);

	/* read the tally counter from the SONIC and reset them */
	lp->stats.rx_crc_errors += SONIC_READ(SONIC_CRCT);
	SONIC_WRITE(SONIC_CRCT, 0xffff);
	lp->stats.rx_frame_errors += SONIC_READ(SONIC_FAET);
	SONIC_WRITE(SONIC_FAET, 0xffff);
	lp->stats.rx_missed_errors += SONIC_READ(SONIC_MPT);
	SONIC_WRITE(SONIC_MPT, 0xffff);

	return &lp->stats;
}