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
struct vsp1_dl_body {TYPE_1__* pool; int /*<<< orphan*/  free; scalar_t__ num_entries; int /*<<< orphan*/  refcnt; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  free; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void vsp1_dl_body_put(struct vsp1_dl_body *dlb)
{
	unsigned long flags;

	if (!dlb)
		return;

	if (!refcount_dec_and_test(&dlb->refcnt))
		return;

	dlb->num_entries = 0;

	spin_lock_irqsave(&dlb->pool->lock, flags);
	list_add_tail(&dlb->free, &dlb->pool->free);
	spin_unlock_irqrestore(&dlb->pool->lock, flags);
}