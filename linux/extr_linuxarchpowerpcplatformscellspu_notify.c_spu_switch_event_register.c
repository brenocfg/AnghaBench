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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int blocking_notifier_chain_register (int /*<<< orphan*/ *,struct notifier_block*) ; 
 int /*<<< orphan*/  notify_spus_active () ; 
 int /*<<< orphan*/  spu_switch_notifier ; 

int spu_switch_event_register(struct notifier_block *n)
{
	int ret;
	ret = blocking_notifier_chain_register(&spu_switch_notifier, n);
	if (!ret)
		notify_spus_active();
	return ret;
}