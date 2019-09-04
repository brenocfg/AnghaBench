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
typedef  int /*<<< orphan*/  u64 ;
struct skb_shared_hwtstamps {int /*<<< orphan*/  hwtstamp; } ;
struct fec_enet_private {int /*<<< orphan*/  tmreg_lock; int /*<<< orphan*/  tc; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct skb_shared_hwtstamps*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timecounter_cyc2time (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void
fec_enet_hwtstamp(struct fec_enet_private *fep, unsigned ts,
	struct skb_shared_hwtstamps *hwtstamps)
{
	unsigned long flags;
	u64 ns;

	spin_lock_irqsave(&fep->tmreg_lock, flags);
	ns = timecounter_cyc2time(&fep->tc, ts);
	spin_unlock_irqrestore(&fep->tmreg_lock, flags);

	memset(hwtstamps, 0, sizeof(*hwtstamps));
	hwtstamps->hwtstamp = ns_to_ktime(ns);
}