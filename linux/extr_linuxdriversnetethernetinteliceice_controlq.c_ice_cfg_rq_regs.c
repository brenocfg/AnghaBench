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
typedef  int u32 ;
struct ice_hw {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  pa; } ;
struct TYPE_4__ {int len_ena_mask; TYPE_1__ desc_buf; int /*<<< orphan*/  bal; int /*<<< orphan*/  tail; int /*<<< orphan*/  bah; int /*<<< orphan*/  len; int /*<<< orphan*/  head; } ;
struct ice_ctl_q_info {int num_rq_entries; TYPE_2__ rq; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int ICE_ERR_AQ_ERROR ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int rd32 (struct ice_hw*,int /*<<< orphan*/ ) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct ice_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum ice_status
ice_cfg_rq_regs(struct ice_hw *hw, struct ice_ctl_q_info *cq)
{
	u32 reg = 0;

	/* Clear Head and Tail */
	wr32(hw, cq->rq.head, 0);
	wr32(hw, cq->rq.tail, 0);

	/* set starting point */
	wr32(hw, cq->rq.len, (cq->num_rq_entries | cq->rq.len_ena_mask));
	wr32(hw, cq->rq.bal, lower_32_bits(cq->rq.desc_buf.pa));
	wr32(hw, cq->rq.bah, upper_32_bits(cq->rq.desc_buf.pa));

	/* Update tail in the HW to post pre-allocated buffers */
	wr32(hw, cq->rq.tail, (u32)(cq->num_rq_entries - 1));

	/* Check one register to verify that config was applied */
	reg = rd32(hw, cq->rq.bal);
	if (reg != lower_32_bits(cq->rq.desc_buf.pa))
		return ICE_ERR_AQ_ERROR;

	return 0;
}