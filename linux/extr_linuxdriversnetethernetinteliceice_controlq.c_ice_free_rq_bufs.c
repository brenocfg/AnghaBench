#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ice_hw {int dummy; } ;
struct TYPE_5__ {TYPE_1__* rq_bi; } ;
struct TYPE_6__ {int /*<<< orphan*/  dma_head; TYPE_2__ r; } ;
struct ice_ctl_q_info {int num_rq_entries; TYPE_3__ rq; } ;
struct TYPE_4__ {scalar_t__ size; scalar_t__ pa; int /*<<< orphan*/ * va; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmam_free_coherent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 

__attribute__((used)) static void ice_free_rq_bufs(struct ice_hw *hw, struct ice_ctl_q_info *cq)
{
	int i;

	/* free descriptors */
	for (i = 0; i < cq->num_rq_entries; i++) {
		dmam_free_coherent(ice_hw_to_dev(hw), cq->rq.r.rq_bi[i].size,
				   cq->rq.r.rq_bi[i].va, cq->rq.r.rq_bi[i].pa);
		cq->rq.r.rq_bi[i].va = NULL;
		cq->rq.r.rq_bi[i].pa = 0;
		cq->rq.r.rq_bi[i].size = 0;
	}

	/* free the dma header */
	devm_kfree(ice_hw_to_dev(hw), cq->rq.dma_head);
}