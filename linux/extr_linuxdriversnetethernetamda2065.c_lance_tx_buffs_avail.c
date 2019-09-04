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
struct lance_private {scalar_t__ tx_old; scalar_t__ tx_new; int tx_ring_mod_mask; } ;

/* Variables and functions */

__attribute__((used)) static int lance_tx_buffs_avail(struct lance_private *lp)
{
	if (lp->tx_old <= lp->tx_new)
		return lp->tx_old + lp->tx_ring_mod_mask - lp->tx_new;
	return lp->tx_old - lp->tx_new - 1;
}