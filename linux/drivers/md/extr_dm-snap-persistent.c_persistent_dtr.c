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
struct pstore {int /*<<< orphan*/  callbacks; scalar_t__ io_client; int /*<<< orphan*/  metadata_wq; } ;
struct dm_exception_store {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_io_client_destroy (scalar_t__) ; 
 int /*<<< orphan*/  free_area (struct pstore*) ; 
 struct pstore* get_info (struct dm_exception_store*) ; 
 int /*<<< orphan*/  kfree (struct pstore*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void persistent_dtr(struct dm_exception_store *store)
{
	struct pstore *ps = get_info(store);

	destroy_workqueue(ps->metadata_wq);

	/* Created in read_header */
	if (ps->io_client)
		dm_io_client_destroy(ps->io_client);
	free_area(ps);

	/* Allocated in persistent_read_metadata */
	vfree(ps->callbacks);

	kfree(ps);
}