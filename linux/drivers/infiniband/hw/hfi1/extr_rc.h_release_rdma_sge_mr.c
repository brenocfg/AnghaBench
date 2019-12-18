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
struct TYPE_2__ {int /*<<< orphan*/ * mr; } ;
struct rvt_ack_entry {TYPE_1__ rdma_sge; } ;

/* Variables and functions */
 int /*<<< orphan*/  rvt_put_mr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void release_rdma_sge_mr(struct rvt_ack_entry *e)
{
	if (e->rdma_sge.mr) {
		rvt_put_mr(e->rdma_sge.mr);
		e->rdma_sge.mr = NULL;
	}
}