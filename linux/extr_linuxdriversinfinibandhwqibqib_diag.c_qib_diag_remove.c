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
struct qib_diag_client {struct qib_diag_client* next; } ;
struct qib_devdata {scalar_t__ diag_client; int /*<<< orphan*/  diag_device; int /*<<< orphan*/  diag_cdev; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 struct qib_diag_client* client_pool ; 
 int /*<<< orphan*/  diagpkt_cdev ; 
 int /*<<< orphan*/  diagpkt_count ; 
 int /*<<< orphan*/  diagpkt_device ; 
 int /*<<< orphan*/  kfree (struct qib_diag_client*) ; 
 int /*<<< orphan*/  qib_cdev_cleanup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qib_unregister_observers (struct qib_devdata*) ; 
 int /*<<< orphan*/  return_client (scalar_t__) ; 

void qib_diag_remove(struct qib_devdata *dd)
{
	struct qib_diag_client *dc;

	if (atomic_dec_and_test(&diagpkt_count))
		qib_cdev_cleanup(&diagpkt_cdev, &diagpkt_device);

	qib_cdev_cleanup(&dd->diag_cdev, &dd->diag_device);

	/*
	 * Return all diag_clients of this device. There should be none,
	 * as we are "guaranteed" that no clients are still open
	 */
	while (dd->diag_client)
		return_client(dd->diag_client);

	/* Now clean up all unused client structs */
	while (client_pool) {
		dc = client_pool;
		client_pool = dc->next;
		kfree(dc);
	}
	/* Clean up observer list */
	qib_unregister_observers(dd);
}