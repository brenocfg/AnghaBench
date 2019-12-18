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
typedef  int /*<<< orphan*/  ulong ;
struct brcmf_fweh_queue_item {int /*<<< orphan*/  q; } ;
struct brcmf_fweh_info {int /*<<< orphan*/  event_work; int /*<<< orphan*/  evt_q_lock; int /*<<< orphan*/  event_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcmf_fweh_queue_event(struct brcmf_fweh_info *fweh,
				   struct brcmf_fweh_queue_item *event)
{
	ulong flags;

	spin_lock_irqsave(&fweh->evt_q_lock, flags);
	list_add_tail(&event->q, &fweh->event_q);
	spin_unlock_irqrestore(&fweh->evt_q_lock, flags);
	schedule_work(&fweh->event_work);
}