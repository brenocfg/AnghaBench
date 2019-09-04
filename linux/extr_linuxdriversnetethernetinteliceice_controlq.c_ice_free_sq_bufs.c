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
struct TYPE_5__ {TYPE_1__* sq_bi; } ;
struct TYPE_6__ {int /*<<< orphan*/  dma_head; int /*<<< orphan*/  cmd_buf; TYPE_2__ r; } ;
struct ice_ctl_q_info {int num_sq_entries; TYPE_3__ sq; } ;
struct TYPE_4__ {scalar_t__ size; scalar_t__ pa; int /*<<< orphan*/ * va; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmam_free_coherent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 

__attribute__((used)) static void ice_free_sq_bufs(struct ice_hw *hw, struct ice_ctl_q_info *cq)
{
	int i;

	/* only unmap if the address is non-NULL */
	for (i = 0; i < cq->num_sq_entries; i++)
		if (cq->sq.r.sq_bi[i].pa) {
			dmam_free_coherent(ice_hw_to_dev(hw),
					   cq->sq.r.sq_bi[i].size,
					   cq->sq.r.sq_bi[i].va,
					   cq->sq.r.sq_bi[i].pa);
			cq->sq.r.sq_bi[i].va = NULL;
			cq->sq.r.sq_bi[i].pa = 0;
			cq->sq.r.sq_bi[i].size = 0;
		}

	/* free the buffer info list */
	devm_kfree(ice_hw_to_dev(hw), cq->sq.cmd_buf);

	/* free the dma header */
	devm_kfree(ice_hw_to_dev(hw), cq->sq.dma_head);
}