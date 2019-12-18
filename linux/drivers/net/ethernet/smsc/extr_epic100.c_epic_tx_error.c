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
struct net_device_stats {int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  tx_window_errors; int /*<<< orphan*/  tx_carrier_errors; int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  tx_errors; } ;
struct net_device {struct net_device_stats stats; } ;
struct epic_private {int dummy; } ;

/* Variables and functions */
 int debug ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int) ; 

__attribute__((used)) static void epic_tx_error(struct net_device *dev, struct epic_private *ep,
			  int status)
{
	struct net_device_stats *stats = &dev->stats;

#ifndef final_version
	/* There was an major error, log it. */
	if (debug > 1)
		netdev_dbg(dev, "Transmit error, Tx status %8.8x.\n",
			   status);
#endif
	stats->tx_errors++;
	if (status & 0x1050)
		stats->tx_aborted_errors++;
	if (status & 0x0008)
		stats->tx_carrier_errors++;
	if (status & 0x0040)
		stats->tx_window_errors++;
	if (status & 0x0010)
		stats->tx_fifo_errors++;
}