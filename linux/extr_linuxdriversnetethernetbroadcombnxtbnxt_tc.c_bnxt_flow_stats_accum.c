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
struct bnxt_tc_info {int /*<<< orphan*/  packets_mask; int /*<<< orphan*/  bytes_mask; } ;
struct bnxt_tc_flow_stats {int /*<<< orphan*/  packets; int /*<<< orphan*/  bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  accumulate_val (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnxt_flow_stats_accum(struct bnxt_tc_info *tc_info,
				  struct bnxt_tc_flow_stats *acc_stats,
				  struct bnxt_tc_flow_stats *hw_stats)
{
	accumulate_val(&acc_stats->bytes, hw_stats->bytes, tc_info->bytes_mask);
	accumulate_val(&acc_stats->packets, hw_stats->packets,
		       tc_info->packets_mask);
}