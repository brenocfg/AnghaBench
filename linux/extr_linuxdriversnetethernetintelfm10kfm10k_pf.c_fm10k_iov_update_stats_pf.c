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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct fm10k_hw_stats_q {int dummy; } ;
struct fm10k_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fm10k_queues_per_pool (struct fm10k_hw*) ; 
 int /*<<< orphan*/  fm10k_update_hw_stats_q (struct fm10k_hw*,struct fm10k_hw_stats_q*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_vf_queue_index (struct fm10k_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fm10k_iov_update_stats_pf(struct fm10k_hw *hw,
				      struct fm10k_hw_stats_q *q,
				      u16 vf_idx)
{
	u32 idx, qpp;

	/* get stats for all of the queues */
	qpp = fm10k_queues_per_pool(hw);
	idx = fm10k_vf_queue_index(hw, vf_idx);
	fm10k_update_hw_stats_q(hw, q, idx, qpp);
}