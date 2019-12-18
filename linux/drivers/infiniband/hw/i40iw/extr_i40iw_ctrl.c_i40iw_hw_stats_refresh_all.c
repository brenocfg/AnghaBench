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
typedef  scalar_t__ u32 ;
struct i40iw_vsi_pestat {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ I40IW_HW_STAT_INDEX_MAX_32 ; 
 scalar_t__ I40IW_HW_STAT_INDEX_MAX_64 ; 
 int /*<<< orphan*/  i40iw_hw_stats_read_32 (struct i40iw_vsi_pestat*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40iw_hw_stats_read_64 (struct i40iw_vsi_pestat*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void i40iw_hw_stats_refresh_all(struct i40iw_vsi_pestat *stats)
{
	u64 stats_value;
	u32 stats_index;
	unsigned long flags;

	spin_lock_irqsave(&stats->lock, flags);

	for (stats_index = 0; stats_index < I40IW_HW_STAT_INDEX_MAX_32;
	     stats_index++)
		i40iw_hw_stats_read_32(stats, stats_index, &stats_value);
	for (stats_index = 0; stats_index < I40IW_HW_STAT_INDEX_MAX_64;
	     stats_index++)
		i40iw_hw_stats_read_64(stats, stats_index, &stats_value);
	spin_unlock_irqrestore(&stats->lock, flags);
}