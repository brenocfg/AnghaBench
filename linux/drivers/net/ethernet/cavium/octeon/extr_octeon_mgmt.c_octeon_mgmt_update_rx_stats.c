#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct octeon_mgmt {int /*<<< orphan*/  lock; scalar_t__ agl; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_errors; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 scalar_t__ AGL_GMX_RX_STATS_PKTS_BAD ; 
 scalar_t__ AGL_GMX_RX_STATS_PKTS_DRP ; 
 scalar_t__ cvmx_read_csr (scalar_t__) ; 
 struct octeon_mgmt* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void octeon_mgmt_update_rx_stats(struct net_device *netdev)
{
	struct octeon_mgmt *p = netdev_priv(netdev);
	unsigned long flags;
	u64 drop, bad;

	/* These reads also clear the count registers.  */
	drop = cvmx_read_csr(p->agl + AGL_GMX_RX_STATS_PKTS_DRP);
	bad = cvmx_read_csr(p->agl + AGL_GMX_RX_STATS_PKTS_BAD);

	if (drop || bad) {
		/* Do an atomic update. */
		spin_lock_irqsave(&p->lock, flags);
		netdev->stats.rx_errors += bad;
		netdev->stats.rx_dropped += drop;
		spin_unlock_irqrestore(&p->lock, flags);
	}
}