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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int __hp_sdc_enqueue_transaction (int /*<<< orphan*/ *) ; 
 TYPE_1__ hp_sdc ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int hp_sdc_enqueue_transaction(hp_sdc_transaction *this) {
	unsigned long flags;
	int ret;

	write_lock_irqsave(&hp_sdc.lock, flags);
	ret = __hp_sdc_enqueue_transaction(this);
	write_unlock_irqrestore(&hp_sdc.lock,flags);

	return ret;
}