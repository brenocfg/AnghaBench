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
typedef  int /*<<< orphan*/  hp_sdc_transaction ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ ** tq; } ;

/* Variables and functions */
 int HP_SDC_QUEUE_LEN ; 
 TYPE_1__ hp_sdc ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int hp_sdc_dequeue_transaction(hp_sdc_transaction *this)
{
	unsigned long flags;
	int i;

	write_lock_irqsave(&hp_sdc.lock, flags);

	/* TODO: don't remove it if it's not done. */

	for (i = 0; i < HP_SDC_QUEUE_LEN; i++)
		if (hp_sdc.tq[i] == this)
			hp_sdc.tq[i] = NULL;

	write_unlock_irqrestore(&hp_sdc.lock, flags);
	return 0;
}