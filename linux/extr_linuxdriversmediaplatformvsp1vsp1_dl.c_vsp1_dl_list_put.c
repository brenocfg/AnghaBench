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
struct vsp1_dl_list {TYPE_1__* dlm; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __vsp1_dl_list_put (struct vsp1_dl_list*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void vsp1_dl_list_put(struct vsp1_dl_list *dl)
{
	unsigned long flags;

	if (!dl)
		return;

	spin_lock_irqsave(&dl->dlm->lock, flags);
	__vsp1_dl_list_put(dl);
	spin_unlock_irqrestore(&dl->dlm->lock, flags);
}