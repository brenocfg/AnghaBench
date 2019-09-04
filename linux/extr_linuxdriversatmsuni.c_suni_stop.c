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
struct suni_priv {struct suni_priv* next; struct atm_dev* dev; } ;
struct atm_dev {int dummy; } ;

/* Variables and functions */
 struct suni_priv* PRIV (struct atm_dev*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct suni_priv*) ; 
 int /*<<< orphan*/  poll_timer ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct suni_priv* sunis ; 
 int /*<<< orphan*/  sunis_lock ; 

__attribute__((used)) static int suni_stop(struct atm_dev *dev)
{
	struct suni_priv **walk;
	unsigned long flags;

	/* let SAR driver worry about stopping interrupts */
	spin_lock_irqsave(&sunis_lock,flags);
	for (walk = &sunis; *walk != PRIV(dev);
	    walk = &PRIV((*walk)->dev)->next);
	*walk = PRIV((*walk)->dev)->next;
	if (!sunis) del_timer_sync(&poll_timer);
	spin_unlock_irqrestore(&sunis_lock,flags);
	kfree(PRIV(dev));

	return 0;
}