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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct i40iw_dev_hw_stats {scalar_t__* stats_value_64; } ;
struct i40iw_dev_hw_stats_offsets {scalar_t__* stats_offset_64; } ;
struct i40iw_vsi_pestat {TYPE_1__* hw; struct i40iw_dev_hw_stats hw_stats; struct i40iw_dev_hw_stats last_read_hw_stats; struct i40iw_dev_hw_stats_offsets hw_stats_offsets; } ;
typedef  enum i40iw_hw_stats_index_64b { ____Placeholder_i40iw_hw_stats_index_64b } i40iw_hw_stats_index_64b ;
struct TYPE_2__ {scalar_t__ hw_addr; } ;

/* Variables and functions */
 scalar_t__ readq (scalar_t__) ; 

void i40iw_hw_stats_read_64(struct i40iw_vsi_pestat *stats,
			    enum i40iw_hw_stats_index_64b index,
			    u64 *value)
{
	struct i40iw_dev_hw_stats_offsets *stats_table =
		&stats->hw_stats_offsets;
	struct i40iw_dev_hw_stats *last_rd_stats = &stats->last_read_hw_stats;
	struct i40iw_dev_hw_stats *hw_stats = &stats->hw_stats;
	u64 new_stats_value = 0;
	u32 stats_reg_offset = stats_table->stats_offset_64[index];

	new_stats_value = readq(stats->hw->hw_addr + stats_reg_offset);
	/*roll-over case */
	if (new_stats_value < last_rd_stats->stats_value_64[index])
		hw_stats->stats_value_64[index] += new_stats_value;
	else
		hw_stats->stats_value_64[index] +=
			new_stats_value - last_rd_stats->stats_value_64[index];
	last_rd_stats->stats_value_64[index] = new_stats_value;
	*value = hw_stats->stats_value_64[index];
}