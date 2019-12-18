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
struct octeon_device {int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  tx_pause; } ;
struct net_device {int dummy; } ;
struct lio {struct octeon_device* oct_dev; } ;
struct ethtool_pauseparam {int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  tx_pause; scalar_t__ autoneg; } ;

/* Variables and functions */
 struct lio* GET_LIO (struct net_device*) ; 

__attribute__((used)) static void
lio_get_pauseparam(struct net_device *netdev, struct ethtool_pauseparam *pause)
{
	/* Notes: Not supporting any auto negotiation in these
	 * drivers. Just report pause frame support.
	 */
	struct lio *lio = GET_LIO(netdev);
	struct octeon_device *oct = lio->oct_dev;

	pause->autoneg = 0;

	pause->tx_pause = oct->tx_pause;
	pause->rx_pause = oct->rx_pause;
}