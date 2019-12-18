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
struct vmci_qp {scalar_t__ blocked; int /*<<< orphan*/  event; int /*<<< orphan*/  generation; } ;

/* Variables and functions */
 int VMCI_SUCCESS ; 
 int /*<<< orphan*/  qp_lock (struct vmci_qp*) ; 
 int /*<<< orphan*/  qp_unlock (struct vmci_qp*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qp_wakeup_cb(void *client_data)
{
	struct vmci_qp *qpair = (struct vmci_qp *)client_data;

	qp_lock(qpair);
	while (qpair->blocked > 0) {
		qpair->blocked--;
		qpair->generation++;
		wake_up(&qpair->event);
	}
	qp_unlock(qpair);

	return VMCI_SUCCESS;
}