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
struct TYPE_4__ {size_t size; int /*<<< orphan*/  va; int /*<<< orphan*/  pa; } ;
struct TYPE_3__ {TYPE_2__ desc_buf; } ;
struct ice_ctl_q_info {int num_rq_entries; TYPE_1__ rq; } ;
struct ice_aq_desc {int dummy; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int ICE_ERR_NO_MEMORY ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  dmam_alloc_coherent (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 

__attribute__((used)) static enum ice_status
ice_alloc_ctrlq_rq_ring(struct ice_hw *hw, struct ice_ctl_q_info *cq)
{
	size_t size = cq->num_rq_entries * sizeof(struct ice_aq_desc);

	cq->rq.desc_buf.va = dmam_alloc_coherent(ice_hw_to_dev(hw), size,
						 &cq->rq.desc_buf.pa,
						 GFP_KERNEL | __GFP_ZERO);
	if (!cq->rq.desc_buf.va)
		return ICE_ERR_NO_MEMORY;
	cq->rq.desc_buf.size = size;
	return 0;
}