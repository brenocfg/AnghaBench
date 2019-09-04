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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  syncp; int /*<<< orphan*/  tx_good_octets; } ;
struct b44 {TYPE_1__ hw_stats; } ;

/* Variables and functions */
 unsigned long B44_RX_GOOD_O ; 
 unsigned long B44_RX_NPAUSE ; 
 unsigned long B44_TX_GOOD_O ; 
 unsigned long B44_TX_PAUSE ; 
 scalar_t__ br32 (struct b44*,unsigned long) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void b44_stats_update(struct b44 *bp)
{
	unsigned long reg;
	u64 *val;

	val = &bp->hw_stats.tx_good_octets;
	u64_stats_update_begin(&bp->hw_stats.syncp);

	for (reg = B44_TX_GOOD_O; reg <= B44_TX_PAUSE; reg += 4UL) {
		*val++ += br32(bp, reg);
	}

	/* Pad */
	reg += 8*4UL;

	for (reg = B44_RX_GOOD_O; reg <= B44_RX_NPAUSE; reg += 4UL) {
		*val++ += br32(bp, reg);
	}

	u64_stats_update_end(&bp->hw_stats.syncp);
}