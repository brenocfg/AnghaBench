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
typedef  int u16 ;
struct TYPE_2__ {int num_vfs; } ;
struct fm10k_hw {TYPE_1__ iov; } ;

/* Variables and functions */
 int FM10K_MAX_QUEUES ; 
 int fm10k_queues_per_pool (struct fm10k_hw*) ; 

u16 fm10k_vf_queue_index(struct fm10k_hw *hw, u16 vf_idx)
{
	u16 num_vfs = hw->iov.num_vfs;
	u16 vf_q_idx = FM10K_MAX_QUEUES;

	vf_q_idx -= fm10k_queues_per_pool(hw) * (num_vfs - vf_idx);

	return vf_q_idx;
}