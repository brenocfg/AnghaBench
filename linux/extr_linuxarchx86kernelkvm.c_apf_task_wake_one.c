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
struct kvm_task_sleep_node {int /*<<< orphan*/  wq; int /*<<< orphan*/  cpu; scalar_t__ halted; int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_send_reschedule (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swake_up_one (int /*<<< orphan*/ *) ; 
 scalar_t__ swq_has_sleeper (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void apf_task_wake_one(struct kvm_task_sleep_node *n)
{
	hlist_del_init(&n->link);
	if (n->halted)
		smp_send_reschedule(n->cpu);
	else if (swq_has_sleeper(&n->wq))
		swake_up_one(&n->wq);
}