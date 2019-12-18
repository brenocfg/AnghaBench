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
struct pnv_php_slot {struct pnv_php_slot* parent; int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pnv_php_lock ; 
 int /*<<< orphan*/  pnv_php_put_slot (struct pnv_php_slot*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void pnv_php_release(struct pnv_php_slot *php_slot)
{
	unsigned long flags;

	/* Remove from global or child list */
	spin_lock_irqsave(&pnv_php_lock, flags);
	list_del(&php_slot->link);
	spin_unlock_irqrestore(&pnv_php_lock, flags);

	/* Detach from parent */
	pnv_php_put_slot(php_slot);
	pnv_php_put_slot(php_slot->parent);
}