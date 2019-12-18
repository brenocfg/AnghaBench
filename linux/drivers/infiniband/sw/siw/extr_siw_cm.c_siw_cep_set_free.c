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
struct siw_cep {int /*<<< orphan*/  waitq; int /*<<< orphan*/  lock; scalar_t__ in_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void siw_cep_set_free(struct siw_cep *cep)
{
	unsigned long flags;

	spin_lock_irqsave(&cep->lock, flags);
	cep->in_use = 0;
	spin_unlock_irqrestore(&cep->lock, flags);

	wake_up(&cep->waitq);
}