#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ice_ctl_q_info {int dummy; } ;
struct ice_hw {struct ice_ctl_q_info adminq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_CQ_INIT_REGS (struct ice_ctl_q_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PF_FW ; 

__attribute__((used)) static void ice_adminq_init_regs(struct ice_hw *hw)
{
	struct ice_ctl_q_info *cq = &hw->adminq;

	ICE_CQ_INIT_REGS(cq, PF_FW);
}