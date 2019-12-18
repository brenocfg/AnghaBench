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
struct garmin_packet {int /*<<< orphan*/  list; } ;
struct TYPE_2__ {scalar_t__ next; } ;
struct garmin_data {int /*<<< orphan*/  lock; TYPE_1__ pktlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct garmin_packet*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void pkt_clear(struct garmin_data *garmin_data_p)
{
	unsigned long flags;
	struct garmin_packet *result = NULL;

	spin_lock_irqsave(&garmin_data_p->lock, flags);
	while (!list_empty(&garmin_data_p->pktlist)) {
		result = (struct garmin_packet *)garmin_data_p->pktlist.next;
		list_del(&result->list);
		kfree(result);
	}
	spin_unlock_irqrestore(&garmin_data_p->lock, flags);
}