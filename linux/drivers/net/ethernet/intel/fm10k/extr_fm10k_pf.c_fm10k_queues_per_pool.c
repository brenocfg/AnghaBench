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
struct TYPE_2__ {int num_pools; } ;
struct fm10k_hw {TYPE_1__ iov; } ;

/* Variables and functions */
 int FM10K_MAX_QUEUES_POOL ; 

u16 fm10k_queues_per_pool(struct fm10k_hw *hw)
{
	u16 num_pools = hw->iov.num_pools;

	return (num_pools > 32) ? 2 : (num_pools > 16) ? 4 : (num_pools > 8) ?
	       8 : FM10K_MAX_QUEUES_POOL;
}