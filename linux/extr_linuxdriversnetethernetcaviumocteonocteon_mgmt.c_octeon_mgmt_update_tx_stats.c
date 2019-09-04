#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ mcol; scalar_t__ scol; } ;
union cvmx_agl_gmx_txx_stat1 {TYPE_3__ s; void* u64; } ;
struct TYPE_4__ {scalar_t__ xscol; scalar_t__ xsdef; } ;
union cvmx_agl_gmx_txx_stat0 {TYPE_1__ s; void* u64; } ;
struct octeon_mgmt {int /*<<< orphan*/  lock; scalar_t__ agl; } ;
struct TYPE_5__ {int /*<<< orphan*/  collisions; int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_2__ stats; } ;

/* Variables and functions */
 scalar_t__ AGL_GMX_TX_STAT0 ; 
 scalar_t__ AGL_GMX_TX_STAT1 ; 
 void* cvmx_read_csr (scalar_t__) ; 
 struct octeon_mgmt* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void octeon_mgmt_update_tx_stats(struct net_device *netdev)
{
	struct octeon_mgmt *p = netdev_priv(netdev);
	unsigned long flags;

	union cvmx_agl_gmx_txx_stat0 s0;
	union cvmx_agl_gmx_txx_stat1 s1;

	/* These reads also clear the count registers.  */
	s0.u64 = cvmx_read_csr(p->agl + AGL_GMX_TX_STAT0);
	s1.u64 = cvmx_read_csr(p->agl + AGL_GMX_TX_STAT1);

	if (s0.s.xsdef || s0.s.xscol || s1.s.scol || s1.s.mcol) {
		/* Do an atomic update. */
		spin_lock_irqsave(&p->lock, flags);
		netdev->stats.tx_errors += s0.s.xsdef + s0.s.xscol;
		netdev->stats.collisions += s1.s.scol + s1.s.mcol;
		spin_unlock_irqrestore(&p->lock, flags);
	}
}