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
struct mdp_kms {int /*<<< orphan*/  in_irq; int /*<<< orphan*/  irq_list; } ;
struct mdp_irq {int registered; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lock ; 
 int /*<<< orphan*/  mdp_irq_update (struct mdp_kms*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void mdp_irq_register(struct mdp_kms *mdp_kms, struct mdp_irq *irq)
{
	unsigned long flags;
	bool needs_update = false;

	spin_lock_irqsave(&list_lock, flags);

	if (!irq->registered) {
		irq->registered = true;
		list_add(&irq->node, &mdp_kms->irq_list);
		needs_update = !mdp_kms->in_irq;
	}

	spin_unlock_irqrestore(&list_lock, flags);

	if (needs_update)
		mdp_irq_update(mdp_kms);
}