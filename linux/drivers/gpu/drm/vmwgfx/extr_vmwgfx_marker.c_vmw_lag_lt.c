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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ u64 ;
struct vmw_marker_queue {int dummy; } ;

/* Variables and functions */
 scalar_t__ NSEC_PER_USEC ; 
 scalar_t__ vmw_fifo_lag (struct vmw_marker_queue*) ; 

__attribute__((used)) static bool vmw_lag_lt(struct vmw_marker_queue *queue,
		       uint32_t us)
{
	u64 cond = (u64) us * NSEC_PER_USEC;

	return vmw_fifo_lag(queue) <= cond;
}