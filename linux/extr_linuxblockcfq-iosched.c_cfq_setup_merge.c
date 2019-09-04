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
struct cfq_queue {int ref; struct cfq_queue* new_cfqq; } ;

/* Variables and functions */
 int cfqq_process_refs (struct cfq_queue*) ; 

__attribute__((used)) static void cfq_setup_merge(struct cfq_queue *cfqq, struct cfq_queue *new_cfqq)
{
	int process_refs, new_process_refs;
	struct cfq_queue *__cfqq;

	/*
	 * If there are no process references on the new_cfqq, then it is
	 * unsafe to follow the ->new_cfqq chain as other cfqq's in the
	 * chain may have dropped their last reference (not just their
	 * last process reference).
	 */
	if (!cfqq_process_refs(new_cfqq))
		return;

	/* Avoid a circular list and skip interim queue merges */
	while ((__cfqq = new_cfqq->new_cfqq)) {
		if (__cfqq == cfqq)
			return;
		new_cfqq = __cfqq;
	}

	process_refs = cfqq_process_refs(cfqq);
	new_process_refs = cfqq_process_refs(new_cfqq);
	/*
	 * If the process for the cfqq has gone away, there is no
	 * sense in merging the queues.
	 */
	if (process_refs == 0 || new_process_refs == 0)
		return;

	/*
	 * Merge in the direction of the lesser amount of work.
	 */
	if (new_process_refs >= process_refs) {
		cfqq->new_cfqq = new_cfqq;
		new_cfqq->ref += process_refs;
	} else {
		new_cfqq->new_cfqq = cfqq;
		cfqq->ref += new_process_refs;
	}
}