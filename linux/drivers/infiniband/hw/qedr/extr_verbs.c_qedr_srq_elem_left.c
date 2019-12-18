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
typedef  scalar_t__ u32 ;
struct qedr_srq_hwq_info {scalar_t__ max_wr; scalar_t__ wr_cons_cnt; scalar_t__ wr_prod_cnt; } ;

/* Variables and functions */

__attribute__((used)) static u32 qedr_srq_elem_left(struct qedr_srq_hwq_info *hw_srq)
{
	u32 used;

	/* Calculate number of elements used based on producer
	 * count and consumer count and subtract it from max
	 * work request supported so that we get elements left.
	 */
	used = hw_srq->wr_prod_cnt - hw_srq->wr_cons_cnt;

	return hw_srq->max_wr - used;
}