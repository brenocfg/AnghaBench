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
struct ice_hw {int dummy; } ;
struct TYPE_2__ {int len_mask; int len_ena_mask; scalar_t__ len; } ;
struct ice_ctl_q_info {int num_sq_entries; TYPE_1__ sq; } ;

/* Variables and functions */
 int rd32 (struct ice_hw*,scalar_t__) ; 

bool ice_check_sq_alive(struct ice_hw *hw, struct ice_ctl_q_info *cq)
{
	/* check both queue-length and queue-enable fields */
	if (cq->sq.len && cq->sq.len_mask && cq->sq.len_ena_mask)
		return (rd32(hw, cq->sq.len) & (cq->sq.len_mask |
						cq->sq.len_ena_mask)) ==
			(cq->num_sq_entries | cq->sq.len_ena_mask);

	return false;
}