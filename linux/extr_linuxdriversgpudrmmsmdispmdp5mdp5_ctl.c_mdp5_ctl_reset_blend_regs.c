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
struct mdp5_ctl_manager {int nlm; } ;
struct mdp5_ctl {int /*<<< orphan*/  hw_lock; int /*<<< orphan*/  id; struct mdp5_ctl_manager* ctlm; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_MDP5_CTL_LAYER_EXT_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_MDP5_CTL_LAYER_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ctl_write (struct mdp5_ctl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mdp5_ctl_reset_blend_regs(struct mdp5_ctl *ctl)
{
	unsigned long flags;
	struct mdp5_ctl_manager *ctl_mgr = ctl->ctlm;
	int i;

	spin_lock_irqsave(&ctl->hw_lock, flags);

	for (i = 0; i < ctl_mgr->nlm; i++) {
		ctl_write(ctl, REG_MDP5_CTL_LAYER_REG(ctl->id, i), 0x0);
		ctl_write(ctl, REG_MDP5_CTL_LAYER_EXT_REG(ctl->id, i), 0x0);
	}

	spin_unlock_irqrestore(&ctl->hw_lock, flags);
}