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
typedef  int u32 ;
struct ocrdma_qp_hwq_info {void* va; int entry_size; } ;

/* Variables and functions */

__attribute__((used)) static void *ocrdma_hwq_head_from_idx(struct ocrdma_qp_hwq_info *q,
				      u32 idx)
{
	return q->va + (idx * q->entry_size);
}