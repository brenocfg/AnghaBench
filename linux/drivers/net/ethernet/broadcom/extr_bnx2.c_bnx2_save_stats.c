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
typedef  int u64 ;
typedef  int u32 ;
struct statistics_block {int dummy; } ;
struct bnx2 {scalar_t__ temp_stats_blk; scalar_t__ stats_blk; } ;

/* Variables and functions */

__attribute__((used)) static void
bnx2_save_stats(struct bnx2 *bp)
{
	u32 *hw_stats = (u32 *) bp->stats_blk;
	u32 *temp_stats = (u32 *) bp->temp_stats_blk;
	int i;

	/* The 1st 10 counters are 64-bit counters */
	for (i = 0; i < 20; i += 2) {
		u32 hi;
		u64 lo;

		hi = temp_stats[i] + hw_stats[i];
		lo = (u64) temp_stats[i + 1] + (u64) hw_stats[i + 1];
		if (lo > 0xffffffff)
			hi++;
		temp_stats[i] = hi;
		temp_stats[i + 1] = lo & 0xffffffff;
	}

	for ( ; i < sizeof(struct statistics_block) / 4; i++)
		temp_stats[i] += hw_stats[i];
}