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
typedef  size_t u32 ;
struct i40iw_vsi_pestat {int /*<<< orphan*/  lock; } ;
struct i40iw_dev_hw_stats {int /*<<< orphan*/ * stats_value_64; int /*<<< orphan*/ * stats_value_32; } ;

/* Variables and functions */
 size_t I40IW_HW_STAT_INDEX_MAX_32 ; 
 size_t I40IW_HW_STAT_INDEX_MAX_64 ; 
 int /*<<< orphan*/  i40iw_hw_stats_read_32 (struct i40iw_vsi_pestat*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40iw_hw_stats_read_64 (struct i40iw_vsi_pestat*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void i40iw_hw_stats_read_all(struct i40iw_vsi_pestat *stats,
			     struct i40iw_dev_hw_stats *stats_values)
{
	u32 stats_index;
	unsigned long flags;

	spin_lock_irqsave(&stats->lock, flags);

	for (stats_index = 0; stats_index < I40IW_HW_STAT_INDEX_MAX_32;
	     stats_index++)
		i40iw_hw_stats_read_32(stats, stats_index,
				       &stats_values->stats_value_32[stats_index]);
	for (stats_index = 0; stats_index < I40IW_HW_STAT_INDEX_MAX_64;
	     stats_index++)
		i40iw_hw_stats_read_64(stats, stats_index,
				       &stats_values->stats_value_64[stats_index]);
	spin_unlock_irqrestore(&stats->lock, flags);
}