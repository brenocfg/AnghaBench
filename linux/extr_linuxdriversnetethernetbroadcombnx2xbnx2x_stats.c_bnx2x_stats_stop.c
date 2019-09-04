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
struct TYPE_2__ {scalar_t__ pmf; } ;
struct bnx2x {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnx2x_hw_stats_post (struct bnx2x*) ; 
 scalar_t__ bnx2x_hw_stats_update (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_net_stats_update (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_port_stats_stop (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_stats_comp (struct bnx2x*) ; 
 scalar_t__ bnx2x_storm_stats_update (struct bnx2x*) ; 

__attribute__((used)) static void bnx2x_stats_stop(struct bnx2x *bp)
{
	bool update = false;

	bnx2x_stats_comp(bp);

	if (bp->port.pmf)
		update = (bnx2x_hw_stats_update(bp) == 0);

	update |= (bnx2x_storm_stats_update(bp) == 0);

	if (update) {
		bnx2x_net_stats_update(bp);

		if (bp->port.pmf)
			bnx2x_port_stats_stop(bp);

		bnx2x_hw_stats_post(bp);
		bnx2x_stats_comp(bp);
	}
}