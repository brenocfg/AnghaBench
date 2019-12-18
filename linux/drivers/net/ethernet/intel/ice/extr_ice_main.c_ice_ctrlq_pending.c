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
typedef  scalar_t__ u16 ;
struct ice_hw {int dummy; } ;
struct TYPE_2__ {int head_mask; scalar_t__ next_to_clean; int /*<<< orphan*/  head; } ;
struct ice_ctl_q_info {TYPE_1__ rq; } ;

/* Variables and functions */
 int rd32 (struct ice_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ice_ctrlq_pending(struct ice_hw *hw, struct ice_ctl_q_info *cq)
{
	u16 ntu;

	ntu = (u16)(rd32(hw, cq->rq.head) & cq->rq.head_mask);
	return cq->rq.next_to_clean != ntu;
}