#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dm_snapshot {int /*<<< orphan*/  pending; int /*<<< orphan*/  pe_allocation_lock; int /*<<< orphan*/  exception_start_sequence; TYPE_2__* store; } ;
struct TYPE_7__ {int /*<<< orphan*/  old_chunk; } ;
struct dm_snap_pending_exception {TYPE_3__ e; scalar_t__ exception_sequence; int /*<<< orphan*/ * full_bio; scalar_t__ started; int /*<<< orphan*/  snapshot_bios; int /*<<< orphan*/  origin_bios; } ;
typedef  int /*<<< orphan*/  chunk_t ;
struct TYPE_6__ {TYPE_1__* type; } ;
struct TYPE_5__ {scalar_t__ (* prepare_exception ) (TYPE_2__*,TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  bio_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_insert_exception (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  free_pending_exception (struct dm_snap_pending_exception*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static struct dm_snap_pending_exception *
__insert_pending_exception(struct dm_snapshot *s,
			   struct dm_snap_pending_exception *pe, chunk_t chunk)
{
	pe->e.old_chunk = chunk;
	bio_list_init(&pe->origin_bios);
	bio_list_init(&pe->snapshot_bios);
	pe->started = 0;
	pe->full_bio = NULL;

	spin_lock(&s->pe_allocation_lock);
	if (s->store->type->prepare_exception(s->store, &pe->e)) {
		spin_unlock(&s->pe_allocation_lock);
		free_pending_exception(pe);
		return NULL;
	}

	pe->exception_sequence = s->exception_start_sequence++;
	spin_unlock(&s->pe_allocation_lock);

	dm_insert_exception(&s->pending, &pe->e);

	return pe;
}