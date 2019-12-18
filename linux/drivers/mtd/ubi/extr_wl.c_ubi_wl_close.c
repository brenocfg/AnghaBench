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
struct ubi_device {int /*<<< orphan*/  lookuptbl; int /*<<< orphan*/  scrub; int /*<<< orphan*/  free; int /*<<< orphan*/  erroneous; int /*<<< orphan*/  used; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_wl (char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  protection_queue_destroy (struct ubi_device*) ; 
 int /*<<< orphan*/  shutdown_work (struct ubi_device*) ; 
 int /*<<< orphan*/  tree_destroy (struct ubi_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_fastmap_close (struct ubi_device*) ; 

void ubi_wl_close(struct ubi_device *ubi)
{
	dbg_wl("close the WL sub-system");
	ubi_fastmap_close(ubi);
	shutdown_work(ubi);
	protection_queue_destroy(ubi);
	tree_destroy(ubi, &ubi->used);
	tree_destroy(ubi, &ubi->erroneous);
	tree_destroy(ubi, &ubi->free);
	tree_destroy(ubi, &ubi->scrub);
	kfree(ubi->lookuptbl);
}