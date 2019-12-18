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
struct tx_ring_info {int max_burst; } ;
struct niu {TYPE_1__* dev; } ;
struct TYPE_2__ {int mtu; } ;

/* Variables and functions */

__attribute__((used)) static void niu_set_max_burst(struct niu *np, struct tx_ring_info *rp)
{
	int mtu = np->dev->mtu;

	/* These values are recommended by the HW designers for fair
	 * utilization of DRR amongst the rings.
	 */
	rp->max_burst = mtu + 32;
	if (rp->max_burst > 4096)
		rp->max_burst = 4096;
}