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
struct kfifo {int dummy; } ;
struct anybuss_host {int /*<<< orphan*/  ind_ab; int /*<<< orphan*/  wq; struct kfifo* qs; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct kfifo*) ; 
 int /*<<< orphan*/  HZ ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  process_qs (struct anybuss_host*) ; 
 int /*<<< orphan*/  process_softint (struct anybuss_host*) ; 
 scalar_t__ qs_have_work (struct kfifo*,size_t) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qthread_fn(void *data)
{
	struct anybuss_host *cd = data;
	struct kfifo *qs = cd->qs;
	size_t nqs = ARRAY_SIZE(cd->qs);
	unsigned int ind_ab;

	/*
	 * this kernel thread has exclusive access to the anybus's memory.
	 * only exception: the IND_AB register, which is accessed exclusively
	 * by the interrupt service routine (ISR). This thread must not touch
	 * the IND_AB register, but it does require access to its value.
	 *
	 * the interrupt service routine stores the register's value in
	 * cd->ind_ab (an atomic_t), where we may safely access it, with the
	 * understanding that it can be modified by the ISR at any time.
	 */

	while (!kthread_should_stop()) {
		/*
		 * make a local copy of IND_AB, so we can go around the loop
		 * again in case it changed while processing queues and softint.
		 */
		ind_ab = atomic_read(&cd->ind_ab);
		process_qs(cd);
		process_softint(cd);
		wait_event_timeout(cd->wq,
				   (atomic_read(&cd->ind_ab) != ind_ab) ||
				qs_have_work(qs, nqs) ||
				kthread_should_stop(),
			HZ);
		/*
		 * time out so even 'stuck' tasks will run eventually,
		 * and can time out.
		 */
	}

	return 0;
}