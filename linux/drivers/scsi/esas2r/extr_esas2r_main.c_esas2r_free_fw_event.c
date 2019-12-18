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
struct esas2r_fw_event_work {int /*<<< orphan*/  list; struct esas2r_adapter* a; } ;
struct esas2r_adapter {int /*<<< orphan*/  fw_event_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct esas2r_fw_event_work*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
esas2r_free_fw_event(struct esas2r_fw_event_work *fw_event)
{
	unsigned long flags;
	struct esas2r_adapter *a = fw_event->a;

	spin_lock_irqsave(&a->fw_event_lock, flags);
	list_del(&fw_event->list);
	kfree(fw_event);
	spin_unlock_irqrestore(&a->fw_event_lock, flags);
}