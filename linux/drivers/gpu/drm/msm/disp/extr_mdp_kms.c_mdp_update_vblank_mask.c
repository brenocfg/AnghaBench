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
typedef  int /*<<< orphan*/  uint32_t ;
struct mdp_kms {int /*<<< orphan*/  vblank_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  update_irq (struct mdp_kms*) ; 

void mdp_update_vblank_mask(struct mdp_kms *mdp_kms, uint32_t mask, bool enable)
{
	unsigned long flags;

	spin_lock_irqsave(&list_lock, flags);
	if (enable)
		mdp_kms->vblank_mask |= mask;
	else
		mdp_kms->vblank_mask &= ~mask;
	update_irq(mdp_kms);
	spin_unlock_irqrestore(&list_lock, flags);
}