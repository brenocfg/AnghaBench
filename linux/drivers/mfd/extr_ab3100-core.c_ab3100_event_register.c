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
struct ab3100 {int /*<<< orphan*/  event_subscribers; } ;

/* Variables and functions */
 int blocking_notifier_chain_register (int /*<<< orphan*/ *,struct notifier_block*) ; 

int ab3100_event_register(struct ab3100 *ab3100,
			  struct notifier_block *nb)
{
	return blocking_notifier_chain_register(&ab3100->event_subscribers,
					       nb);
}