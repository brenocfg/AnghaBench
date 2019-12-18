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
struct net_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLAN_DBG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLAN_DEBUG_GNRL ; 
 int /*<<< orphan*/  TLAN_IGNORE ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  tlan_free_lists (struct net_device*) ; 
 int /*<<< orphan*/  tlan_read_and_clear_stats (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlan_reset_adapter (struct net_device*) ; 
 int /*<<< orphan*/  tlan_reset_lists (struct net_device*) ; 

__attribute__((used)) static void tlan_tx_timeout(struct net_device *dev)
{

	TLAN_DBG(TLAN_DEBUG_GNRL, "%s: Transmit timed out.\n", dev->name);

	/* Ok so we timed out, lets see what we can do about it...*/
	tlan_free_lists(dev);
	tlan_reset_lists(dev);
	tlan_read_and_clear_stats(dev, TLAN_IGNORE);
	tlan_reset_adapter(dev);
	netif_trans_update(dev); /* prevent tx timeout */
	netif_wake_queue(dev);

}