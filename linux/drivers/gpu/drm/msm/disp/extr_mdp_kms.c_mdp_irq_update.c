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
struct mdp_kms {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  update_irq (struct mdp_kms*) ; 

void mdp_irq_update(struct mdp_kms *mdp_kms)
{
	unsigned long flags;
	spin_lock_irqsave(&list_lock, flags);
	update_irq(mdp_kms);
	spin_unlock_irqrestore(&list_lock, flags);
}