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
struct dm_kcopyd_client {int /*<<< orphan*/  job_pool; int /*<<< orphan*/  io_client; int /*<<< orphan*/  kcopyd_wq; int /*<<< orphan*/  pages_jobs; int /*<<< orphan*/  io_jobs; int /*<<< orphan*/  complete_jobs; int /*<<< orphan*/  callback_jobs; int /*<<< orphan*/  nr_jobs; int /*<<< orphan*/  destroyq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  client_free_pages (struct dm_kcopyd_client*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_io_client_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dm_kcopyd_client*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mempool_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void dm_kcopyd_client_destroy(struct dm_kcopyd_client *kc)
{
	/* Wait for completion of all jobs submitted by this client. */
	wait_event(kc->destroyq, !atomic_read(&kc->nr_jobs));

	BUG_ON(!list_empty(&kc->callback_jobs));
	BUG_ON(!list_empty(&kc->complete_jobs));
	BUG_ON(!list_empty(&kc->io_jobs));
	BUG_ON(!list_empty(&kc->pages_jobs));
	destroy_workqueue(kc->kcopyd_wq);
	dm_io_client_destroy(kc->io_client);
	client_free_pages(kc);
	mempool_exit(&kc->job_pool);
	kfree(kc);
}