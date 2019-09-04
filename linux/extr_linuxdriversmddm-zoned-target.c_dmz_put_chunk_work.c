#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dm_chunk_work {int /*<<< orphan*/  chunk; TYPE_1__* target; int /*<<< orphan*/  bio_list; int /*<<< orphan*/  refcount; } ;
struct TYPE_2__ {int /*<<< orphan*/  chunk_rxtree; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dm_chunk_work*) ; 
 int /*<<< orphan*/  radix_tree_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dmz_put_chunk_work(struct dm_chunk_work *cw)
{
	if (atomic_dec_and_test(&cw->refcount)) {
		WARN_ON(!bio_list_empty(&cw->bio_list));
		radix_tree_delete(&cw->target->chunk_rxtree, cw->chunk);
		kfree(cw);
	}
}