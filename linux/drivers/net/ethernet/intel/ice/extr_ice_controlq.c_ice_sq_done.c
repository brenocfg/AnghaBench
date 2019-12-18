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
struct TYPE_2__ {scalar_t__ next_to_use; int /*<<< orphan*/  head; } ;
struct ice_ctl_q_info {TYPE_1__ sq; } ;

/* Variables and functions */
 scalar_t__ rd32 (struct ice_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ice_sq_done(struct ice_hw *hw, struct ice_ctl_q_info *cq)
{
	/* AQ designers suggest use of head for better
	 * timing reliability than DD bit
	 */
	return rd32(hw, cq->sq.head) == cq->sq.next_to_use;
}