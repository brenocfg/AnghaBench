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
typedef  int u32 ;
struct mdp5_pipeline {TYPE_1__* mixer; } ;
struct mdp5_ctl_manager {int flush_hw_mask; } ;
struct mdp5_ctl {struct mdp5_ctl_manager* ctlm; } ;
struct TYPE_2__ {int /*<<< orphan*/  lm; } ;

/* Variables and functions */
 int MDP5_CTL_FLUSH_CURSOR_0 ; 
 int mdp_ctl_flush_mask_lm (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 fix_sw_flush(struct mdp5_ctl *ctl, struct mdp5_pipeline *pipeline,
			u32 flush_mask)
{
	struct mdp5_ctl_manager *ctl_mgr = ctl->ctlm;
	u32 sw_mask = 0;
#define BIT_NEEDS_SW_FIX(bit) \
	(!(ctl_mgr->flush_hw_mask & bit) && (flush_mask & bit))

	/* for some targets, cursor bit is the same as LM bit */
	if (BIT_NEEDS_SW_FIX(MDP5_CTL_FLUSH_CURSOR_0))
		sw_mask |= mdp_ctl_flush_mask_lm(pipeline->mixer->lm);

	return sw_mask;
}