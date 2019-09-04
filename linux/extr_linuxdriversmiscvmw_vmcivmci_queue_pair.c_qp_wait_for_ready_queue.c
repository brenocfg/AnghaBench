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
struct vmci_qp {unsigned int generation; int /*<<< orphan*/  event; int /*<<< orphan*/  blocked; } ;

/* Variables and functions */
 int /*<<< orphan*/  qp_lock (struct vmci_qp*) ; 
 int /*<<< orphan*/  qp_unlock (struct vmci_qp*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool qp_wait_for_ready_queue(struct vmci_qp *qpair)
{
	unsigned int generation;

	qpair->blocked++;
	generation = qpair->generation;
	qp_unlock(qpair);
	wait_event(qpair->event, generation != qpair->generation);
	qp_lock(qpair);

	return true;
}