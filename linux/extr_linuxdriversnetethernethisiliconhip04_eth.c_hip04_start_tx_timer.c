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
struct hip04_priv {int tx_coalesce_usecs; int /*<<< orphan*/  tx_coalesce_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int NSEC_PER_USEC ; 
 int /*<<< orphan*/  hrtimer_start_range_ns (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_to_ktime (unsigned long) ; 

__attribute__((used)) static void hip04_start_tx_timer(struct hip04_priv *priv)
{
	unsigned long ns = priv->tx_coalesce_usecs * NSEC_PER_USEC / 2;

	/* allow timer to fire after half the time at the earliest */
	hrtimer_start_range_ns(&priv->tx_coalesce_timer, ns_to_ktime(ns),
			       ns, HRTIMER_MODE_REL);
}