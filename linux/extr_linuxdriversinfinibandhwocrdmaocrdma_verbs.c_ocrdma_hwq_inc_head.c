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
struct ocrdma_qp_hwq_info {int head; int max_wqe_idx; } ;

/* Variables and functions */

__attribute__((used)) static void ocrdma_hwq_inc_head(struct ocrdma_qp_hwq_info *q)
{
	q->head = (q->head + 1) & q->max_wqe_idx;
}