#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/  count; } ;
struct fm10k_hw_stats {int stats_idx; int /*<<< orphan*/  q; TYPE_2__ nodesc_drop; TYPE_2__ loopback_drop; TYPE_2__ vlan_drop; TYPE_2__ xec; TYPE_2__ um; TYPE_2__ ca; TYPE_2__ ur; TYPE_2__ timeout; } ;
struct TYPE_4__ {int /*<<< orphan*/  max_queues; } ;
struct fm10k_hw {TYPE_1__ mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_STATS_CA ; 
 int /*<<< orphan*/  FM10K_STATS_LOOPBACK_DROP ; 
 int /*<<< orphan*/  FM10K_STATS_NODESC_DROP ; 
 int /*<<< orphan*/  FM10K_STATS_TIMEOUT ; 
 int /*<<< orphan*/  FM10K_STATS_UM ; 
 int /*<<< orphan*/  FM10K_STATS_UR ; 
 int /*<<< orphan*/  FM10K_STATS_VLAN_DROP ; 
 int /*<<< orphan*/  FM10K_STATS_XEC ; 
 int FM10K_STAT_VALID ; 
 int /*<<< orphan*/  FM10K_TXQCTL (int /*<<< orphan*/ ) ; 
 int FM10K_TXQCTL_ID_MASK ; 
 int fm10k_read_hw_stats_32b (struct fm10k_hw*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int fm10k_read_reg (struct fm10k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_update_hw_base_32b (TYPE_2__*,int) ; 
 int /*<<< orphan*/  fm10k_update_hw_stats_q (struct fm10k_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fm10k_update_hw_stats_pf(struct fm10k_hw *hw,
				     struct fm10k_hw_stats *stats)
{
	u32 timeout, ur, ca, um, xec, vlan_drop, loopback_drop, nodesc_drop;
	u32 id, id_prev;

	/* Use Tx queue 0 as a canary to detect a reset */
	id = fm10k_read_reg(hw, FM10K_TXQCTL(0));

	/* Read Global Statistics */
	do {
		timeout = fm10k_read_hw_stats_32b(hw, FM10K_STATS_TIMEOUT,
						  &stats->timeout);
		ur = fm10k_read_hw_stats_32b(hw, FM10K_STATS_UR, &stats->ur);
		ca = fm10k_read_hw_stats_32b(hw, FM10K_STATS_CA, &stats->ca);
		um = fm10k_read_hw_stats_32b(hw, FM10K_STATS_UM, &stats->um);
		xec = fm10k_read_hw_stats_32b(hw, FM10K_STATS_XEC, &stats->xec);
		vlan_drop = fm10k_read_hw_stats_32b(hw, FM10K_STATS_VLAN_DROP,
						    &stats->vlan_drop);
		loopback_drop =
			fm10k_read_hw_stats_32b(hw,
						FM10K_STATS_LOOPBACK_DROP,
						&stats->loopback_drop);
		nodesc_drop = fm10k_read_hw_stats_32b(hw,
						      FM10K_STATS_NODESC_DROP,
						      &stats->nodesc_drop);

		/* if value has not changed then we have consistent data */
		id_prev = id;
		id = fm10k_read_reg(hw, FM10K_TXQCTL(0));
	} while ((id ^ id_prev) & FM10K_TXQCTL_ID_MASK);

	/* drop non-ID bits and set VALID ID bit */
	id &= FM10K_TXQCTL_ID_MASK;
	id |= FM10K_STAT_VALID;

	/* Update Global Statistics */
	if (stats->stats_idx == id) {
		stats->timeout.count += timeout;
		stats->ur.count += ur;
		stats->ca.count += ca;
		stats->um.count += um;
		stats->xec.count += xec;
		stats->vlan_drop.count += vlan_drop;
		stats->loopback_drop.count += loopback_drop;
		stats->nodesc_drop.count += nodesc_drop;
	}

	/* Update bases and record current PF id */
	fm10k_update_hw_base_32b(&stats->timeout, timeout);
	fm10k_update_hw_base_32b(&stats->ur, ur);
	fm10k_update_hw_base_32b(&stats->ca, ca);
	fm10k_update_hw_base_32b(&stats->um, um);
	fm10k_update_hw_base_32b(&stats->xec, xec);
	fm10k_update_hw_base_32b(&stats->vlan_drop, vlan_drop);
	fm10k_update_hw_base_32b(&stats->loopback_drop, loopback_drop);
	fm10k_update_hw_base_32b(&stats->nodesc_drop, nodesc_drop);
	stats->stats_idx = id;

	/* Update Queue Statistics */
	fm10k_update_hw_stats_q(hw, stats->q, 0, hw->mac.max_queues);
}