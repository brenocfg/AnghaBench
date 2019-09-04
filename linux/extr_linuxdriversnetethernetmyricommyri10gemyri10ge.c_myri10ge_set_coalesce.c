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
struct myri10ge_priv {int /*<<< orphan*/  intr_coal_delay_ptr; int /*<<< orphan*/  intr_coal_delay; } ;
struct ethtool_coalesce {int /*<<< orphan*/  rx_coalesce_usecs; } ;

/* Variables and functions */
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 struct myri10ge_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  put_be32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
myri10ge_set_coalesce(struct net_device *netdev, struct ethtool_coalesce *coal)
{
	struct myri10ge_priv *mgp = netdev_priv(netdev);

	mgp->intr_coal_delay = coal->rx_coalesce_usecs;
	put_be32(htonl(mgp->intr_coal_delay), mgp->intr_coal_delay_ptr);
	return 0;
}