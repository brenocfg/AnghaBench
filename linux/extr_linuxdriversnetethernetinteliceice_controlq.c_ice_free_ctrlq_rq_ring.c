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
struct ice_hw {int dummy; } ;
struct TYPE_4__ {scalar_t__ size; scalar_t__ pa; int /*<<< orphan*/ * va; } ;
struct TYPE_3__ {TYPE_2__ desc_buf; } ;
struct ice_ctl_q_info {TYPE_1__ rq; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmam_free_coherent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 

__attribute__((used)) static void ice_free_ctrlq_rq_ring(struct ice_hw *hw, struct ice_ctl_q_info *cq)
{
	dmam_free_coherent(ice_hw_to_dev(hw), cq->rq.desc_buf.size,
			   cq->rq.desc_buf.va, cq->rq.desc_buf.pa);
	cq->rq.desc_buf.va = NULL;
	cq->rq.desc_buf.pa = 0;
	cq->rq.desc_buf.size = 0;
}