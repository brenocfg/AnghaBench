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
 int /*<<< orphan*/  gmac_dump_dma_state (struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 

__attribute__((used)) static void gmac_tx_timeout(struct net_device *netdev)
{
	netdev_err(netdev, "Tx timeout\n");
	gmac_dump_dma_state(netdev);
}