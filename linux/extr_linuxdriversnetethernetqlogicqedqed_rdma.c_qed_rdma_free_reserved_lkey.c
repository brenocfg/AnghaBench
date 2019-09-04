#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qed_hwfn {TYPE_2__* p_rdma_info; } ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  reserved_lkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  qed_rdma_free_tid (struct qed_hwfn*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qed_rdma_free_reserved_lkey(struct qed_hwfn *p_hwfn)
{
	qed_rdma_free_tid(p_hwfn, p_hwfn->p_rdma_info->dev->reserved_lkey);
}