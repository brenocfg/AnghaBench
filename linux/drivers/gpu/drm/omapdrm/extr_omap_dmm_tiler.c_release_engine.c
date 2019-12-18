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
struct refill_engine {int /*<<< orphan*/  idle_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  engine_queue; int /*<<< orphan*/  engine_counter; int /*<<< orphan*/  idle_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lock ; 
 TYPE_1__* omap_dmm ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void release_engine(struct refill_engine *engine)
{
	unsigned long flags;

	spin_lock_irqsave(&list_lock, flags);
	list_add(&engine->idle_node, &omap_dmm->idle_head);
	spin_unlock_irqrestore(&list_lock, flags);

	atomic_inc(&omap_dmm->engine_counter);
	wake_up_interruptible(&omap_dmm->engine_queue);
}